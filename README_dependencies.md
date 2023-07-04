# Dependencies

Note about install commands:

- for Windows, we use [choco](https://chocolatey.org/install) or just download the installer and install.
- for MacOS, we use [brew](https://brew.sh/).
- In case of an error in cmake, make sure that the dependencies are on the PATH.

## Too Long, Didn't Install

This is a really long list of dependencies, and it's easy to mess up. That's why:

### Docker

We have a Docker image that's already set up for you. See the

<!-- markdownlint-disable MD051 -->

[Docker instructions](#docker-instructions).

<!-- markdownlint-enable -->

### Necessary Dependencies

1. A C++ compiler that supports nearly all of C++17 and most of C++20.
   See [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support)
   to see which features are supported by each compiler.
   The following compilers should work:

   - [gcc 12+](https://gcc.gnu.org/)
     Install command

     - Debian/Ubuntu:

       ```bash
       sudo apt install build-essential
       ```

     - Windows: N/A
     - MacOS:

       ```bash
       brew install gcc
       ```

   - [clang 15+](https://clang.llvm.org/)
     Install command

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

   - [Visual Studio 2022 or higher](https://visualstudio.microsoft.com/)
     Install command + Environment setup

     On Windows, you need to install Visual Studio 2019 because of the SDK and
     libraries that ship with it.

2. [CMake 3.25+](https://cmake.org/)
   Install Command

   - Debian/Ubuntu:

     ```bash
     sudo apt-get install cmake
     ```

   - Windows: Download latest version of CMake and install: [CMake](https://cmake.org/download/)
   - MacOS:

     ```bash
     brew install cmake
     ```

### Optional Dependencies

#### C++ Tools

- [Doxygen](http://doxygen.nl/)
  Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install doxygen
    sudo apt-get install graphviz
    ```

  - Windows: Download latest version of Doxygen and install: [Doxygen](https://www.doxygen.nl/download.html)

  - MacOS:

    ```bash
    brew install doxygen
    brew install graphviz
    ```

- [ccache](https://ccache.dev)
  Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install ccache
    ```

  - Windows: Download latest version of ccache and install: [Cache](https://ccache.dev/download.html)

  - MacOS:

    ```bash
    brew install ccache
    ```

- [Cppcheck](http://cppcheck.sourceforge.net/)
  Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install cppcheck
    ```

  - Windows: Download latest version and install: [Cppcheck](https://cppcheck.sourceforge.io/)

  - MacOS:

    ```bash
    brew install cppcheck
    ```

- [include-what-you-use](https://include-what-you-use.org/)
  Install Command

  Follow instructions here:
  [install: include what you use](https://github.com/include-what-you-use/include-what-you-use#how-to-install)
