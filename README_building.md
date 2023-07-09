# Build Instructions

A full build has different steps:

1. Specifying the compiler using environment variables
2. Configuring the project
3. Building the project

For the subsequent builds, in case you change the source code, you only need to
repeat the last step.

## (1) Specify the compiler using environment variables

By default (if you don't set environment variables `CC` and `CXX`), the system
default compiler will be used.

CMake uses the environment variables CC and CXX to decide which compiler to use.
So to avoid the conflict issues only specify the compilers using these
variables.

### Commands for setting the compilers

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

## (2) Configure your build

To configure the project, you could use `cmake`, or `ccmake` or `cmake-gui`.
Each of them are explained in the following:

### (2.a) Configuring via cmake

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

### (2.b) Configuring via ccmake

With the Cmake Curses Dialog Command Line tool:

```bash
ccmake -S . -B ./build
```

Once `ccmake` has finished setting up, press 'c' to configure the project, press
'g' to generate, and 'q' to quit.

### (2.c) Configuring via cmake-gui

To use the GUI of the cmake:

2.c.1) Open cmake-gui from the project directory:

```bash
cmake-gui .
```

2.c.2) Set the build directory:

![build_dir](https://user-images.githubusercontent.com/16418197/82524586-fa48e380-9af4-11ea-8514-4e18a063d8eb.jpg)

2.c.3) Configure the generator:

In cmake-gui, from the upper menu select `Tools/Configure`.

**Warning**: if you have set `CC` and `CXX` always choose the
`use default native compilers` option. This picks `CC` and `CXX`. Don't change
the compiler at this stage!

#### Windows - Visual Studio generator and Clang Compiler

You should have already set `C` and `CXX` to `clang.exe` and `clang++.exe`.

Choose "Visual Studio 17 2022" as the generator. To tell Visual studio to use
`clang-cl.exe`:

- If you use the LLVM that is shipped with Visual Studio: write `ClangCl` under
  "optional toolset to use".

![visual_studio](https://user-images.githubusercontent.com/16418197/82781142-ae60ac00-9e1e-11ea-8c77-222b005a8f7e.png)

2.c.4) Choose the Cmake options and then generate:

![generate](https://user-images.githubusercontent.com/16418197/82781591-c97feb80-9e1f-11ea-86c8-f2748b96f516.png)

### (3) Build the project

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

### Running the tests

You can use the `ctest` command run the tests.

```bash
cd ./build
ctest -C Debug
cd ../
```
