#!/usr/bin/env python
'''A wrapper script around clang-format, suitable for linting multiple files
and to use for continuous integration.

This is an alternative API for the clang-format command line.
It runs over multiple files and directories in parallel.
A diff output is produced and a sensible exit code is returned.

'''

import argparse
import codecs
import difflib
import errno
import io
import multiprocessing
import os
import signal
import subprocess
import sys
import traceback
from functools import partial

import pathspec
from pyparsing import Iterator

DEFAULT_EXTENSIONS = 'c,h,C,H,cpp,hpp,cc,hh,c++,h++,cxx,hxx'

BASE_PATH = os.path.dirname(
    os.path.normpath(os.path.realpath(os.path.expanduser(__file__))))
DEFAULT_CLANG_FORMAT_IGNORE = os.path.join(BASE_PATH, '.clang-format-ignore')
DEFAULT_CLANG_FORMAT_INCLUDE = os.path.join(BASE_PATH, '.clang-format-include')


class ExitStatus:
    SUCCESS = 0
    DIFF = 1
    TROUBLE = 2


def list_from_file(ignore_file: str) -> list[str]:
    return_list = []
    try:
        with io.open(ignore_file, 'r', encoding='utf-8') as fd:
            for line in fd:
                if line.startswith('#'):
                    # ignore comments
                    continue
                pattern = line.rstrip()
                if not pattern:
                    # allow empty lines
                    continue
                return_list.append(pattern)
    except EnvironmentError as e:
        if e.errno != errno.ENOENT:
            raise
    return return_list


def list_files(
        files: list[str],
        recursive: bool = False,
        extensions: bool = None,
        exclude: list[str] = None) -> list[str]:
    if extensions is None:
        extensions = []
    if exclude is None:
        exclude = []
    if files is None:
        files = []

    out = []
    files.extend(list_from_file(DEFAULT_CLANG_FORMAT_INCLUDE))

    patterns = map(pathspec.patterns.GitWildMatchPattern, exclude)
    spec = pathspec.PathSpec(patterns)

    for file in files:
        if recursive and os.path.isdir(file):
            for dirpath, _, fnames in os.walk(file):
                full_paths = [os.path.join(dirpath, fname) for fname in fnames]
                full_paths = [x for x in full_paths if not spec.match_file(x)]
                for full_path in full_paths:
                    ext = os.path.splitext(full_path)[1][1:]
                    if ext in extensions:
                        out.append(full_path)
        else:
            out.append(file)
    return out


def make_diff(file: str, original: str, reformatted: str) -> list[str]:
    return list(
        difflib.unified_diff(
            original,
            reformatted,
            fromfile=f'{file}\t(original)',
            tofile=f'{file}\t(reformatted)',
            n=3))


class DiffError(Exception):

    def __init__(self, message: str, errs=None) -> None:
        super().__init__(message)
        self.errs = errs or []


class UnexpectedError(Exception):

    def __init__(self, message: str, exc=None) -> None:
        super().__init__(message)
        self.formatted_traceback = traceback.format_exc()
        self.exc = exc


def run_clang_format_diff_wrapper(args: argparse.Namespace,
                                  file: str) -> tuple[list, list]:
    try:
        ret = run_clang_format_diff(args, file)
        return ret
    except DiffError:
        raise
    except Exception as e:
        raise UnexpectedError(f'{file}: {e.__class__.__name__}: {e}', e) from e


def run_clang_format_diff(args: argparse.Namespace,
                          file: str) -> tuple[list, list]:
    try:
        with io.open(file, 'r', encoding='utf-8') as fd:
            original = fd.readlines()
    except IOError as exc:
        raise DiffError(str(exc)) from exc

    if args.in_place:
        invocation = [args.clang_format_executable, '-i', file]
    else:
        invocation = [args.clang_format_executable, file]

    if args.style:
        invocation.extend(['--style', args.style])

    if args.dry_run:
        print(' '.join(invocation))
        return [], []

    # Use of utf-8 to decode the process output.
    #
    # Hopefully, this is the correct thing to do.
    #
    # It's done due to the following assumptions (which may be incorrect):
    # - clang-format will returns the bytes read from the files as-is,
    #   without conversion, and it is already assumed that the files use utf-8.
    # - if the diagnostics were internationalized, they would use utf-8:
    #   > Adding Translations to Clang
    #   >
    #   > Not possible yet!
    #   > Diagnostic strings should be written in UTF-8,
    #   > the client can translate to the relevant code page if needed.
    #   > Each translation completely replaces the format string
    #   > for the diagnostic.
    #   > -- http://clang.llvm.org/docs/InternalsManual.html#internals-diag-translation # pylint: disable=line-too-long
    #
    # It's not pretty, due to Python 2 & 3 compatibility.
    encoding_py3 = {}
    if sys.version_info[0] >= 3:
        encoding_py3['encoding'] = 'utf-8'

    try:
        with subprocess.Popen(invocation,
                              stdout=subprocess.PIPE,
                              stderr=subprocess.PIPE,
                              universal_newlines=True,
                              **encoding_py3) as proc:
            proc_stdout = proc.stdout
            proc_stderr = proc.stderr
            if sys.version_info[0] < 3:
                # make the pipes compatible with Python 3,
                # reading lines should output unicode
                encoding = 'utf-8'
                proc_stdout = codecs.getreader(encoding)(proc_stdout)
                proc_stderr = codecs.getreader(encoding)(proc_stderr)
            # hopefully the stderr pipe won't get full and block the process
            outs = list(proc_stdout.readlines())
            errs = list(proc_stderr.readlines())
            proc.wait()
            if proc.returncode:
                error_string = (
                    f'Command "{subprocess.list2cmdline(invocation)}" '
                    f'returned non-zero exit status {proc.returncode}')
                raise DiffError(error_string, errs)
    except OSError as exc:
        error_string = f'Command "{invocation}" failed to start: {exc}'
        raise DiffError(error_string) from exc
    if args.in_place:
        return [], errs
    return make_diff(file, original, outs), errs


def bold_red(s: str) -> str:
    return '\x1b[1m\x1b[31m' + s + '\x1b[0m'


def colorize(diff_lines: list[str]) -> Iterator:

    def bold(s: str) -> str:
        return '\x1b[1m' + s + '\x1b[0m'

    def cyan(s: str) -> str:
        return '\x1b[36m' + s + '\x1b[0m'

    def green(s: str) -> str:
        return '\x1b[32m' + s + '\x1b[0m'

    def red(s: str) -> str:
        return '\x1b[31m' + s + '\x1b[0m'

    for line in diff_lines:
        if line[:4] in ['--- ', '+++ ']:
            yield bold(line)
        elif line.startswith('@@ '):
            yield cyan(line)
        elif line.startswith('+'):
            yield green(line)
        elif line.startswith('-'):
            yield red(line)
        else:
            yield line


def print_diff(diff_lines: list[str], use_color: bool) -> None:
    if use_color:
        diff_lines = colorize(diff_lines)
    if sys.version_info[0] < 3:
        sys.stdout.writelines((l.encode('utf-8') for l in diff_lines))
    else:
        sys.stdout.writelines(diff_lines)


def print_trouble(prog: str, message: str, use_colors: bool) -> None:
    error_text = 'error:'
    if use_colors:
        error_text = bold_red(error_text)
    print(f'{prog}: {error_text} {message}', file=sys.stderr)


def cli_arguments() -> tuple[argparse.Namespace, argparse.ArgumentParser]:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        '--clang-format-executable',
        metavar='EXECUTABLE',
        help='path to the clang-format executable',
        default='clang-format')
    extensions_help = (
        'comma separated list of file extensions (default: '
        f'{DEFAULT_EXTENSIONS})')
    parser.add_argument(
        '--extensions', help=extensions_help, default=DEFAULT_EXTENSIONS)
    parser.add_argument(
        '-r',
        '--recursive',
        action='store_true',
        help='run recursively over directories')
    parser.add_argument(
        '-d',
        '--dry-run',
        action='store_true',
        help='just print the list of files')
    parser.add_argument(
        '-i',
        '--in-place',
        action='store_true',
        help='format file instead of printing differences')
    parser.add_argument('--files', metavar='file', nargs='+')
    parser.add_argument(
        '-q',
        '--quiet',
        action='store_true',
        help='disable output, useful for the exit code')
    parser.add_argument(
        '-j',
        metavar='N',
        type=int,
        default=0,
        help='run N clang-format jobs in parallel'
        ' (default number of cpus + 1)')
    parser.add_argument(
        '--color',
        default='auto',
        choices=['auto', 'always', 'never'],
        help='show colored diff (default: auto)')
    parser.add_argument(
        '-e',
        '--exclude',
        metavar='PATTERN',
        action='append',
        default=[],
        help='exclude paths matching the given glob-like pattern(s)'
        ' from recursive search')
    parser.add_argument(
        '--style',
        help=
        'formatting style to apply (LLVM, Google, Chromium, Mozilla, WebKit)')

    args = parser.parse_args()
    return args, parser


def run_pool_job(
    it: Iterator,
    parser: argparse.ArgumentParser,
    colored_stderr: bool = False,
    is_quiet: bool = False,
    colored_stdout: bool = False,
) -> None:
    while True:
        try:
            outs, errs = next(it)
        except StopIteration:
            break
        except DiffError as e:
            print_trouble(parser.prog, str(e), use_colors=colored_stderr)
            return_code = ExitStatus.TROUBLE
            sys.stderr.writelines(e.errs)
        except UnexpectedError as e:
            print_trouble(parser.prog, str(e), use_colors=colored_stderr)
            sys.stderr.write(e.formatted_traceback)
            return_code = ExitStatus.TROUBLE
            # stop at the first unexpected error,
            # something could be very wrong,
            # don't process all files unnecessarily
            break
        else:
            sys.stderr.writelines(errs)
            if outs == []:
                continue
            if not is_quiet:
                print_diff(outs, use_color=colored_stdout)
            if return_code == ExitStatus.SUCCESS:
                return_code = ExitStatus.DIFF


def main():
    args, parser = cli_arguments()

    # use default signal handling, like diff return SIGINT value on ^C
    # https://bugs.python.org/issue14229#msg156446
    signal.signal(signal.SIGINT, signal.SIG_DFL)
    try:
        signal.SIGPIPE
    except AttributeError:
        # compatibility, SIGPIPE does not exist on Windows
        pass
    else:
        signal.signal(signal.SIGPIPE, signal.SIG_DFL)

    colored_stdout = False
    colored_stderr = False
    if args.color == 'always':
        colored_stdout = True
        colored_stderr = True
    elif args.color == 'auto':
        colored_stdout = sys.stdout.isatty()
        colored_stderr = sys.stderr.isatty()

    version_invocation = [args.clang_format_executable, str('--version')]
    try:
        subprocess.check_call(version_invocation, stdout=subprocess.DEVNULL)
    except subprocess.CalledProcessError as e:
        print_trouble(parser.prog, str(e), use_colors=colored_stderr)
        return ExitStatus.TROUBLE
    except OSError as e:
        error_string = (
            f'Command "{subprocess.list2cmdline(version_invocation)}" '
            f'failed to start: {e}')
        print_trouble(parser.prog, error_string, use_colors=colored_stderr)
        return ExitStatus.TROUBLE

    return_code = ExitStatus.SUCCESS

    excludes = list_from_file(DEFAULT_CLANG_FORMAT_IGNORE)
    excludes.extend(args.exclude)

    files = list_files(
        args.files,
        recursive=args.recursive,
        exclude=excludes,
        extensions=args.extensions.split(','))

    if not files:
        return

    number_of_jobs = args.j
    if number_of_jobs == 0:
        number_of_jobs = multiprocessing.cpu_count() + 1
    number_of_jobs = min(len(files), number_of_jobs)

    if number_of_jobs == 1:
        # execute directly instead of in a pool,
        # less overhead, simpler stacktraces
        it = (run_clang_format_diff_wrapper(args, file) for file in files)
        run_pool_job(it, parser, colored_stderr, args.quiet, colored_stdout)
    else:
        with multiprocessing.Pool(number_of_jobs) as pool:
            it = pool.imap_unordered(
                partial(run_clang_format_diff_wrapper, args), files)
            run_pool_job(it, parser, colored_stderr, args.quiet, colored_stdout)
    return return_code


if __name__ == '__main__':
    sys.exit(main())
