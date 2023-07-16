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
    - [Too Long, Didn't Install](#too-long-didnt-install)
      - [Docker](#docker)
      - [Necessary Dependencies](#necessary-dependencies)
      - [Optional Dependencies](#optional-dependencies)
        - [C++ Tools](#c-tools)
  - [Build Instructions](#build-instructions)
    - [(1) Specify the compiler using environment variables](#1-specify-the-compiler-using-environment-variables)
      - [Commands for setting the compilers](#commands-for-setting-the-compilers)
    - [(2) Configure your build](#2-configure-your-build)
      - [(2.a) Configuring via cmake](#2a-configuring-via-cmake)
      - [(2.b) Configuring via ccmake](#2b-configuring-via-ccmake)
      - [(2.c) Configuring via cmake-gui](#2c-configuring-via-cmake-gui)
        - [Windows - Visual Studio generator and Clang Compiler](#windows---visual-studio-generator-and-clang-compiler)
      - [(3) Build the project](#3-build-the-project)
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

- for Windows, we use [choco][] or just download the installer and install.
- for MacOS, we use [brew][].
- In case of an error in cmake, make sure that the dependencies are on the PATH.

### Too Long, Didn't Install

This is a really long list of dependencies, and it's easy to mess up. That's
why:

#### Docker

We have a Docker image that's already set up for you. See the

[Docker instructions](#docker-instructions).

#### Necessary Dependencies

1. A C++ compiler that supports nearly all of C++17 and most of C++20.

   - See [C++ Reference][] to see which features are supported by each compiler.
     The following compilers should work:

   - [gcc 12+](https://gcc.gnu.org/) Install command

     - Debian/Ubuntu:

       ```bash
       sudo apt install build-essential
       ```

     - Windows: N/A
     - MacOS:

       ```bash
       brew install gcc
       ```

   - [clang 15+](https://clang.llvm.org/) Install command

     - Debian/Ubuntu:

       ```bash
       bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
       ```

     - Windows:

       Visual Studio 2022 ships with LLVM (see the Visual Studio section).

     - MacOS:

       ```bash
       brew install llvm
       ```

   - [Visual Studio 2022 or higher][] Install command + Environment setup

     On Windows, you need to install Visual Studio 2019 because of the SDK and
     libraries that ship with it.

2. [CMake 3.25+][] Install Command

   - Debian/Ubuntu:

     ```bash
     sudo apt-get install cmake
     ```

   - Windows: Download latest version of CMake and install: [CMake Download][]
   - MacOS:

     ```bash
     brew install cmake
     ```

#### Optional Dependencies

##### C++ Tools

- [Doxygen][] Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install doxygen
    sudo apt-get install graphviz
    ```

  - Windows: Download latest version of Doxygen and install:

    - [Doxygen Download][]

  - MacOS:

    ```bash
    brew install doxygen
    brew install graphviz
    ```

- [ccache][] Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install ccache
    ```

  - Windows: Download latest version of ccache and install: [ccache download][]

  - MacOS:

    ```bash
    brew install ccache
    ```

- [cppcheck][] Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install cppcheck
    ```

  - Windows: Download latest version and install: [cppcheck][]

  - MacOS:

    ```bash
    brew install cppcheck
    ```

- [include-what-you-use][] Install Command

  Follow instructions here: [install: include what you use][]

## Build Instructions

A full build has different steps:

1. Specifying the compiler using environment variables
2. Configuring the project
3. Building the project

For the subsequent builds, in case you change the source code, you only need to
repeat the last step.

### (1) Specify the compiler using environment variables

By default (if you don't set environment variables `CC` and `CXX`), the system
default compiler will be used.

CMake uses the environment variables CC and CXX to decide which compiler to use.
So to avoid the conflict issues only specify the compilers using these
variables.

#### Commands for setting the compilers

- Debian/Ubuntu/MacOS Set your desired compiler (`clang`, `gcc`, etc):

  - Temporarily (only for the current shell)
  - Run one of the following in the terminal:

    - clang

    ```bash
    CC=clang CXX=clang++
    ```

    - gcc

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

### (2) Configure your build

To configure the project, you could use `cmake`, or `ccmake` or `cmake-gui`.
Each of them are explained in the following:

#### (2.a) Configuring via cmake

With Cmake directly:

```bash
cmake -S . -B ./build
```

Cmake will automatically create the `./build` folder if it does not exist, and
it will configure the project.

Instead, if you have CMake version 3.25+, you can use one of the configuration
presets that are listed in the CmakePresets.json file.

```bash
cmake . --preset <configure-preset>
cmake --build
```

#### (2.b) Configuring via ccmake

With the Cmake Curses Dialog Command Line tool:

```bash
ccmake -S . -B ./build
```

Once `ccmake` has finished setting up, press 'c' to configure the project, press
'g' to generate, and 'q' to quit.

#### (2.c) Configuring via cmake-gui

To use the GUI of the cmake:

2.c.1) Open cmake-gui from the project directory:

```bash
cmake-gui .
```

2.c.2) Set the build directory:

![build_dir][]

2.c.3) Configure the generator:

In cmake-gui, from the upper menu select `Tools/Configure`.

**Warning**: if you have set `CC` and `CXX` always choose the
`use default native compilers` option. This picks `CC` and `CXX`. Don't change
the compiler at this stage!

##### Windows - Visual Studio generator and Clang Compiler

You should have already set `C` and `CXX` to `clang.exe` and `clang++.exe`.

Choose "Visual Studio 17 2022" as the generator. To tell Visual studio to use
`clang-cl.exe`:

- If you use the LLVM that is shipped with Visual Studio: write `ClangCl` under
  "optional toolset to use".

![visual_studio][]

2.c.4) Choose the Cmake options and then generate:

![generate][]

#### (3) Build the project

Once you have selected all the options you would like to use, you can build the
project (all targets):

```bash
cmake --build ./build
```

For Visual Studio, give the build configuration (Release, RelWithDeb, Debug,
etc) like the following:

```bash
cmake --build ./build -- /p:configuration=Release
```

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

This command will put you in a `bash` session in a Ubuntu 22.04 Docker
container, with all of the tools listed in the [Dependencies](#dependencies)
section already installed. Additionally, you will have `g++-12` and `clang++-16`
installed as the default versions of `g++` and `clang++`.

If you want to build this container using some other versions of gcc and clang,
you may do so with the `GCC_VER` and `LLVM_VER` arguments:

```bash
docker build --tag=myproject:latest --build-arg GCC_VER=12 --build-arg LLVM_VER=16 .
```

The CC and CXX environment variables are set to GCC version 12 by default. If
you wish to use clang as your default CC and CXX environment variables, you may
do so like this:

```bash
docker build --tag=my_project:latest --build-arg USE_CLANG=1 .
```

You will be logged in as root, so you will see the `#` symbol as your prompt.
You will be in a directory that contains a copy of the `cpp_starter_project`;
any changes you make to your local copy will not be updated in the Docker image
until you rebuild it. If you need to mount your local copy directly in the
Docker image, see [Docker volumes docs][]. TLDR:

```bash
docker run -it \
  -v absolute_path_on_host_machine:absolute_path_in_guest_container \
  my_project:latest
```

You can configure and build [as directed above](#build-instructions) using these
commands:

```bash
/starter_project# mkdir build
/starter_project# cmake -S . -B ./build
/starter_project# cmake --build ./build
```

You can configure and build using `clang-16`, without rebuilding the container,
with these commands:

```bash
/starter_project# mkdir build
/starter_project# CC=clang CXX=clang++ cmake -S . -B ./build
/starter_project# cmake --build ./build
```

The `ccmake` tool is also installed; you can substitute `ccmake` for `cmake` to
configure the project interactively. All of the tools this project supports are
installed in the Docker image; enabling them is as simple as flipping a switch
using the `ccmake` interface. Be aware that some of the sanitizers conflict with
each other, so be sure to run them separately.

A script called `build_examples.sh` is provided to help you to build the example
GUI projects in this container.

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
  https://github.com/jamielapointe/modern_cpp_template/actions/workflows/codeql-analysis.yml/badge.svg
[codeql]:
  https://github.com/jamielapointe/modern_cpp_template/actions/workflows/codeql-analysis.yml
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
[choco]: https://chocolatey.org/install
[brew]: https://brew.sh/
[C++ Reference]: https://en.cppreference.com/w/cpp/compiler_support
[Visual Studio 2022 or higher]: https://visualstudio.microsoft.com/
[CMake 3.25+]: https://cmake.org/
[CMake Download]: https://cmake.org/download/
[Doxygen]: http://doxygen.nl/
[Doxygen Download]: https://www.doxygen.nl/download.html
[ccache]: https://ccache.dev
[ccache download]: https://ccache.dev/download.html
[include-what-you-use]: https://include-what-you-use.org/
[install: include what you use]:
  https://github.com/include-what-you-use/include-what-you-use#how-to-install
[build_dir]:
  https://user-images.githubusercontent.com/16418197/82524586-fa48e380-9af4-11ea-8514-4e18a063d8eb.jpg
[visual_studio]:
  https://user-images.githubusercontent.com/16418197/82781142-ae60ac00-9e1e-11ea-8c77-222b005a8f7e.png
[generate]:
  https://user-images.githubusercontent.com/16418197/82781591-c97feb80-9e1f-11ea-86c8-f2748b96f516.png
[Docker]: https://www.docker.com/
[Docker volumes docs]: https://docs.docker.com/storage/volumes/
[all-contributors]: https://github.com/all-contributors/all-contributors

<!-- [conan-badge]: https://img.shields.io/badge/conan-io-blue -->
<!-- [conan-link]: https://conan.io/center/myproject -->
