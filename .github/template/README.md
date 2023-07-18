# %%myproject%%

[![CI Actions Status][ci-badge]][ci]
[![CodeQL Actions Status][codeql-badge]][codeql]
[![Code Coverage][codecov-badge]][codecov]
[![Codacy Badge][codacy-badge]][codacy]

<!-- [![Latest GitHub release][releases-badge]][github releases] -->
<!-- [![Gitter chat][gitter-badge]][gitter] -->
<!-- [![Conan.io][conan-badge]][conan-link] -->
<!-- markdownlint-disable -->
## Table of Contents

- [%%myproject%%](#%%myproject%%)
  - [Table of Contents](#table-of-contents)
  - [About %%myproject%%](#about-%%myproject%%)
  - [Technologies Used](#technologies-used)
  - [Dependencies](#dependencies)
    - [Docker](#docker)
      - [Necessary Dependencies](#necessary-dependencies)
      - [Optional Dependencies](#optional-dependencies)
        - [C++ Tools](#c-tools)
  - [Setup/Installation Requirements](#setupinstallation-requirements)
    - [Specify the compiler using environment variables](#specify-the-compiler-using-environment-variables)
      - [Commands for setting the compilers](#commands-for-setting-the-compilers)
    - [Configure your build](#configure-your-build)
      - [Running the tests](#running-the-tests)
  - [Docker Instructions](#docker-instructions)
  - [Known Bugs](#known-bugs)
  - [Contribute](#contribute)
  - [License](#license)

## About %%myproject%%

%%description%%

## Technologies Used

- _List all_
- _the major technologies_
- _you used in your project_
- _here_

Current list:

- C++ 20
- Third Party Tools:
  - [CPM][]
    - CMake package management
  - [fmt][]
    - Formatted printing
  - [spdlog][]
    - Logging
  - [CLI11][]
    - Command line interface and argument parser
  - [GSL: Guidelines Support Library][]
    - Helping adhere to the [C++ Core Guidelines]
  - [Abseil][]
    - Helping to adhere to the [Google C++ styleguide][]
- Tools to help enhance the quality of the code:
  - [Google Test][]
    - Unit testing
  - [Google Benchmark][]
    - Micro-benchmarking runtime performance
  - [pre-commit][]
    - Helping ensure adherence to a common styleguide for other text based (non
      C++)
  - [clang-format][]
    - Helping ensure adherence to a common C++ styleguide
  - [clang-tidy][]
    - Static analyzer to help to enforce coding standards such as
      - [SEI CERT C++ Coding Standard][]
      - [Google C++ styleguide][]
      - [C++ Core Guidelines][]
  - [cppcheck][]
    - Additional static analyzer
  - [codeql][]
    - Additional static analyzer to help ensure secure code
  - [codacy][]
    - Additional static analyzer to help ensure secure code and monitor test
      code coverage

## Dependencies

Note about install commands:

- In case of an error in cmake, make sure that the dependencies are on the PATH.
- Currently the instructions are only for Debian/Ubuntu Linux; We hope to add
  additional operating systems in the future.

### Docker

We have a Docker image that's already set up for you. See the

[Docker instructions](#docker-instructions).

#### Necessary Dependencies

1. A C++ compiler that supports nearly all of C++17 and most of C++20.

   - See [C++ Reference][] to see which features are supported by each compiler.
     The following compilers should work:

   - [gcc 12+](https://gcc.gnu.org/) Install command

     - Debian/Ubuntu:

       ```bash
       sudo apt-get install build-essential gcovr gcc-12 g++-12 gcc-12-doc
       ```

   - [clang 16+](https://clang.llvm.org/) Install command

     - Debian/Ubuntu:

       ```bash
       wget https://apt.llvm.org/llvm.sh
       chmod +x llvm.sh
       sudo ./llvm.sh 16 all
       ```

2. [CMake 3.25+][] Install Command

   - Debian/Ubuntu:

     ```bash
     sudo apt-get install cmake
     ```

#### Optional Dependencies

##### C++ Tools

- [ninja][] Install Command

  - A small build system with a focus on speed

  ```bash
  sudo apt-get install ninja-build
  ```

- [Doxygen][] 1.9.7

  - Generate API documentation from source code
  - Debian/Ubuntu:

    ```bash
    sudo apt-get install graphviz texlive-latex-extra ghostscript
    wget https://www.doxygen.nl/files/doxygen-1.9.7.linux.bin.tar.gz \
      mkdir -p "${HOME}/.local" \
      tar -xC "${HOME}/.local" -f doxygen-1.9.7.linux.bin.tar.gz \
      rm doxygen-1.9.7.linux.bin.tar.gz \
      echo "export PATH=\"${HOME}/.local/doxygen-1.9.7/bin:${PATH}\"" >> "${HOME}/.bashrc" \
      export PATH="${HOME}/.local/doxygen-1.9.7/bin:${PATH}" \
    ```

- [ccache][]

  - Compiler cache
  - Debian/Ubuntu:

    ```bash
    sudo apt-get install ccache
    ```

- [cppcheck][]

  - C/C++ static analysis tool
  - Debian/Ubuntu:

    ```bash
    sudo apt-get install cppcheck
    ```

  - Windows: Download latest version and install: [cppcheck][]

- [libpfm-4][]

  - a helper library to program the performance monitoring event

  ```bash
  sudo apt-get install libpfm4
  ```

- [include-what-you-use][]

  - Optimize usage of `#include` C & C++ instructions
  - Follow instructions here: [install: include what you use][]

## Setup/Installation Requirements

- _This is a great place_
- _to list setup instructions_
- _in a simple_
- _easy-to-understand_
- _format_

- _This is a great place_
- _to list setup instructions_
- _in a simple_
- _easy-to-understand_
- _format_

### Specify the compiler using environment variables

By default (if you don't set environment variables `CC` and `CXX`), the system
default compiler will be used. For Debian/Ubuntu this is usually the default
version of GCC.

CMake uses the environment variables `CC` and `CXX` to decide which compiler to
use. So to avoid the conflict issues only specify the compilers using these
variables.

#### Commands for setting the compilers

- Debian/Ubuntu Set your desired compiler (`clang`, `gcc`, etc):

  - Temporarily (only for the current shell)
  - Run one of the following in the terminal:

    - clang

    ```bash
    CC=clang CXX=clang++
    ```

    - gcc (usually the default; however, if not, then...)

    ```bash
    CC=gcc CXX=g++
    ```

  - Permanent:
  - Open `~/.bashrc` using your text editor:

    ```bash
    gedit ~/.bashrc
    ```

  - Add `CC` and `CXX` to point to the compilers:

    ```bash
    export CC=clang
    export CXX=clang++
    ```

  - Save and close the file

### Configure your build

To configure the project, you could use `cmake`, or `ccmake` or `cmake-gui`. It
is assumed the user knows how to build software.

#### Running the tests

You can use the `ctest` command run the tests.

```bash
cd ./build
ctest -C Debug
cd ../
```

- _Provide any additional details_
- _concerning testing your project_
- _or other special build options_
- _such as building documentation,_
- _etc._

## Docker Instructions

If you have [Docker][] installed, you can run this in your terminal, when the
Dockerfile is inside the `.devcontainer` directory:

```bash
docker build -f ./.devcontainer/Dockerfile --tag=my_project:latest .
docker run -it my_project:latest
```

- _Provide additional instructions_
- _for building the docker project_
- _and definitely modify the dockerfile_
- _for your specific project_

## Known Bugs

- _Any known issues_
- _should go here_

## Contribute

- _If your project allows third_
- _party contributors, then list_
- _the rules and instructions here_
- _with a links to_
  - _CONTRIBUTING.md which contains rules & instructors for contributors_
  - _CONTRIBUTORS.md which is an autogenerated list of contributors from a tool
    like all-contributor_

## License

- _List which license you are utilizing_
- _for your project_
- _provide a link to the LICENSE.md_
- _file for your project_

[ci-badge]:
  https://github.com/%%myorg%%/%%myproject%%/actions/workflows/ci.yml/badge.svg
[ci]: https://github.com/%%myorg%%/%%myproject%%/actions/workflows/ci.yml
[codecov-badge]:
  https://codecov.io/gh/%%myorg%%/%%myproject%%/branch/main/graph/badge.svg?token=6REP7VM7DP
[codecov]: https://codecov.io/gh/%%myorg%%/%%myproject%%
[codeql-badge]:
  https://github.com/%%myorg%%/%%myproject%%/actions/workflows/codeql_analysis.yml/badge.svg
[codeql]:
  https://github.com/%%myorg%%/%%myproject%%/actions/workflows/codeql_analysis.yml
[codacy-badge]:
  https://app.codacy.com/project/badge/Grade/a709a287b12249c3a4a57165f3306411
[codacy]:
  https://app.codacy.com/gh/%%myorg%%/%%myproject%%/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade
[Google C++ styleguide]: https://google.github.io/styleguide/cppguide.html
[C++ Core Guidelines]:
  https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md
[SEI CERT C++ Coding Standard]:
  https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=88046682
[CPM]: https://github.com/cpm-cmake/CPM.cmake
[Google Test]: https://github.com/google/googletest
[Google Benchmark]: https://github.com/google/benchmark
[fmt]: https://github.com/fmtlib/fmt
[spdlog]: https://github.com/gabime/spdlog
[GSL: Guidelines Support Library]: https://github.com/microsoft/GSL
[Abseil]: https://github.com/abseil/abseil-cpp
[CLI11]: https://github.com/CLIUtils/CLI11
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
[clang-tidy]: https://clang.llvm.org/extra/clang-tidy/
[cppcheck]: https://cppcheck.sourceforge.io/
[pre-commit]: https://pre-commit.com/
[CMake 3.25+]: https://cmake.org/
[Doxygen]: http://doxygen.nl/
[ccache]: https://ccache.dev
[include-what-you-use]: https://include-what-you-use.org/
[install: include what you use]:
  https://github.com/include-what-you-use/include-what-you-use#how-to-install
[Docker]: https://www.docker.com/
[ninja]: https://ninja-build.org/
[libpfm-4]: https://github.com/wcohen/libpfm4
[C++ Reference]: https://en.cppreference.com/w/cpp/compiler_support

<!-- Create conan package manager and add these badges to our project -->
<!-- [conan-badge]: https://img.shields.io/badge/conan-io-blue -->
<!-- [conan-link]: https://conan.io/center/%%myproject%% -->

<!-- If you have a glitter lobby, then add the proper links to your project's -->
<!-- lobby below -->
<!-- [gitter-badge]: https://badges.gitter.im/jl-modern-cpp-template/Lobby.svg -->
<!-- [gitter]: https://gitter.im/jl-modern-cpp-template/Lobby -->

<!-- Add a badge for the latest release of your software -->
<!-- [releases-badge]: https://img.shields.io/badge/%%myproject%%-v0.0.0-blue -->
<!-- [github releases]: ps://github.com/%%myorg%%/%%myproject%%/releases -->
