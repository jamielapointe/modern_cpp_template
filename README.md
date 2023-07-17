# modern_cpp_template: A CMake based template for C++20 development

[![CI Actions Status][ci-badge]][ci]
[![CodeQL Actions Status][codeql-badge]][codeql]
[![Code Coverage][codecov-badge]][codecov]
[![Codacy Badge][codacy-badge]][codacy]

[![Gitter chat][gitter-badge]][gitter]
[![Latest GitHub release][releases-badge]][github releases]

<!-- [![Conan.io][conan-badge]][conan-link] -->

modern_cpp_template is a CMake based template for getting up and running with
modern C++ quickly.

## Table of Contents

- [modern\_cpp\_template: A CMake based template for C++20 development](#modern_cpp_template-a-cmake-based-template-for-c20-development)
  - [Table of Contents](#table-of-contents)
  - [Background](#background)
    - [Introduction](#introduction)
  - [Getting Started](#getting-started)
    - [Use the Github template](#use-the-github-template)
  - [Dependencies](#dependencies)
    - [Docker](#docker)
      - [Necessary Dependencies](#necessary-dependencies)
      - [Optional Dependencies](#optional-dependencies)
        - [C++ Tools](#c-tools)
  - [Build Instructions](#build-instructions)
    - [Specify the compiler using environment variables](#specify-the-compiler-using-environment-variables)
      - [Commands for setting the compilers](#commands-for-setting-the-compilers)
    - [Configure your build](#configure-your-build)
      - [Running the tests](#running-the-tests)
  - [Docker Instructions](#docker-instructions)
  - [Contribute](#contribute)
  - [License](#license)

## Background

### Introduction

This is a fork of [cpp-best-practices/cmake_template][] mostly to be used for my
own personal projects.

This template project uses C++20 and currently supports recent compilers:

- gcc 12
- LLVM/clang 16

Other requirements:

- cmake >= 3.25

This has only been tested on Ubuntu 22.04, though it should work on any desktop
OS with a recent compiler supporting C++ 20.

Optional dependencies:

- doxygen >= 1.9.7
- ccache >= 4.5.1
- cppcheck >= 2.7
- pfm (performance monitoring events library) >= 4.11.1

This template:

- Aggressively sets compiler warnings and sets warnings as errors
- Utilizes clang-format, clang-tidy, & cppcheck
  - [Google C++ styleguide][]
  - [C++ Core Guidelines][]
  - [SEI CERT C++ Coding Standard][]
- Enables Address, Undefined Behavior, and Leak sanitizers whenever possible
- Utilizes [CPM][] for dependency management in CMake
- Utilizes [Google Test][] and [Google Benchmark][]
- Utilizes [fmt][] for formatted printing
- Utilizes [spdlog][] for logging
- Utilizes [GSL: Guidelines Support Library][] for helping to adhere to the
  - [C++ Core Guidelines][]
- Utilizes [Abseil][] helping to adhere to the [Google C++ styleguide][]
- Utilizes [CLI11][] command line utility
- Runs code coverage over the unit tests
- Provides a simple [CLI11][] example
- Locally we utilize [pre-commit][] to helping ensure adherence to a common
  styleguide as mentioned in the [contributing](./.github/CONTRIBUTING.md)
  notes.
- Makes use of [clang-format][], [clang-tidy][], [cppcheck][], [codeql][], and
  [codacy][].

## Getting Started

### Use the Github template

First follow the instructions for generating a project from a template (there
are multiple options) from [using a github template][].

After creating the project please wait until the cleanup workflow has finished
setting up your project and committed the changes.

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

## Build Instructions

A full build has different steps:

1. Specifying the compiler using environment variables
2. Configuring the project
3. Building the project

For the subsequent builds, in case you change the source code, you only need to
repeat the last step.

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
is assumed the user knows how to build software. If not, then there are many
great resource online.

#### Running the tests

You can use the `ctest` command run the tests.

```bash
cd ./build
ctest -C Debug
cd ../
```

## Docker Instructions

If you have [Docker][] installed, you can run this in your terminal, when the
Dockerfile is inside the `.devcontainer` directory:

```bash
docker build -f ./.devcontainer/Dockerfile --tag=my_project:latest .
docker run -it my_project:latest
```

## Contribute

To contribute, open an [issue][github issues] or [pull
request][github pull requests] on GitHub, or ask a question on [gitter][]. There
is also a short note to contributors [here](./.github/CONTRIBUTING.md).

The list of contributors to the project can be found
[here](./.github/CONTRIBUTORS.md).

## License

This template is available as free and unencumbered software into the pubic
domain. See the [LICENSE](./LICENSE) file for details.

This project follows the [all-contributors][] specification. Contributions of
any kind welcome!

[cpp-best-practices/cmake_template]:
  https://github.com/cpp-best-practices/cmake_template
[ci-badge]:
  https://github.com/jamielapointe/modern_cpp_template/actions/workflows/ci.yml/badge.svg
[ci]:
  https://github.com/jamielapointe/modern_cpp_template/actions/workflows/ci.yml
[codecov-badge]:
  https://codecov.io/gh/jamielapointe/modern_cpp_template/branch/main/graph/badge.svg?token=6REP7VM7DP
[codecov]: https://codecov.io/gh/jamielapointe/modern_cpp_template
[codeql-badge]:
  https://github.com/jamielapointe/modern_cpp_template/actions/workflows/codeql_analysis.yml/badge.svg
[codeql]:
  https://github.com/jamielapointe/modern_cpp_template/actions/workflows/codeql_analysis.yml
[codacy-badge]:
  https://app.codacy.com/project/badge/Grade/a709a287b12249c3a4a57165f3306411
[codacy]:
  https://app.codacy.com/gh/jamielapointe/modern_cpp_template/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade
[github issues]: https://github.com/jamielapointe/modern_cpp_template/issues
[github pull requests]:
  https://github.com/jamielapointe/modern_cpp_template/pulls
[github releases]: ps://github.com/jamielapointe/modern_cpp_template/releases
[releases-badge]: https://img.shields.io/badge/myproject-v0.0.0-blue
[gitter-badge]: https://badges.gitter.im/jl-modern-cpp-template/Lobby.svg
[gitter]: https://gitter.im/jl-modern-cpp-template/Lobby
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
[using a github template]:
  https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template
[C++ Reference]: https://en.cppreference.com/w/cpp/compiler_support
[CMake 3.25+]: https://cmake.org/
[Doxygen]: http://doxygen.nl/
[ccache]: https://ccache.dev
[include-what-you-use]: https://include-what-you-use.org/
[install: include what you use]:
  https://github.com/include-what-you-use/include-what-you-use#how-to-install
[Docker]: https://www.docker.com/
[all-contributors]: https://github.com/all-contributors/all-contributors
[ninja]: https://ninja-build.org/
[libpfm-4]: https://github.com/wcohen/libpfm4

<!-- [conan-badge]: https://img.shields.io/badge/conan-io-blue -->
<!-- [conan-link]: https://conan.io/center/myproject -->
