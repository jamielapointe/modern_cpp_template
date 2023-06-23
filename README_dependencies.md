# Dependencies

Note about install commands:

- for Windows, we use [choco](https://chocolatey.org/install).
- for MacOS, we use [brew](https://brew.sh/).
- In case of an error in cmake, make sure that the dependencies are on the PATH.

## Too Long, Didn't Install

This is a really long list of dependencies, and it's easy to mess up. That's why:

### Docker

We have a Docker image that's already set up for you. See the

<!-- markdownlint-disable MD051 -->

[Docker instructions](#docker-instructions).

<!-- markdownlint-enable -->

## Setup-cpp

We have [setup-cpp](https://github.com/aminya/setup-cpp) that is a cross-platform
tool to install all the compilers and dependencies on the system.

Please check [the setup-cpp documentation](https://github.com/aminya/setup-cpp)
or more information.

For example, on Windows, you can run the following to install llvm, cmake, ninja,
ccache, and cppcheck.

```ps1
# windows example (open shell as admin)
curl -LJO "https://github.com/aminya/setup-cpp/releases/download/v0.5.7/setup_cpp_windows.exe"
./setup_cpp_windows --compiler llvm --cmake true --ninja true --ccache true
--cppcheck true

RefreshEnv.cmd # reload the environment
```

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

     - Windows:

       ```bash
       choco install mingw -y
       ```

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

       Visual Studio 2019 ships with LLVM (see the Visual Studio section).
       However, to install LLVM separately:

       ```bash
       choco install llvm -y
       ```

       llvm-utils for using external LLVM with Visual Studio generator:

       ```bash
       git clone https://github.com/zufuliu/llvm-utils.git
       cd llvm-utils/VS2017
       install.bat
       ```

     - MacOS:

       ```bash
       brew install llvm
       ```

   - [Visual Studio 2019 or higher](https://visualstudio.microsoft.com/)
     Install command + Environment setup

     On Windows, you need to install Visual Studio 2019 because of the SDK and
     libraries that ship with it.

     Visual Studio IDE - 2019 Community (installs Clang too):

     ```bash
     choco install -y visualstudio2019community --package-parameters
     "add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended
     --includeOptional --passive --locale en-US"
     ```

     Put MSVC compiler, Clang compiler, and vcvarsall.bat on the path:

     ```bash
     choco install vswhere -y
     refreshenv

     # change to x86 for 32bit
     $clpath = vswhere -products * -latest -prerelease -find **/Hostx64/x64/*
     $clangpath = vswhere -products * -latest -prerelease -find **/Llvm/bin/*
     $vcvarsallpath =  vswhere -products * -latest -prerelease -find **/Auxiliary/Build/*

     $path = [System.Environment]::GetEnvironmentVariable("PATH", "User")
     [Environment]::SetEnvironmentVariable("Path", $path + ";$clpath" + ";$clangpath" + ";$vcvarsallpath", "User")
     refreshenv
     ```

2. [CMake 3.25+](https://cmake.org/)
   Install Command

   - Debian/Ubuntu:

     ```bash
     sudo apt-get install cmake
     ```

   - Windows:

     ```bash
     choco install cmake -y
     ```

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

  - Windows:

    ```bash
    choco install doxygen.install -y
    choco install graphviz -y
    ```

  - MacOS:

    ```bash
    brew install doxygen
    brew install graphviz
    ```

- [ccache][def]
  Install Command

  - Debian/Ubuntu:

    ```bash
    sudo apt-get install ccache
    ```

  - Windows:

    ```bash
    choco install ccache -y
    ```

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

  - Windows:

    ```bash
    choco install cppcheck -y
    ```

  - MacOS:

    ```bash
    brew install cppcheck
    ```

- [include-what-you-use](https://include-what-you-use.org/)
  Install Command

  Follow instructions here:
  [install: include what you use](https://github.com/include-what-you-use/include-what-you-use#how-to-install)

[def]: https://ccache.dev/
