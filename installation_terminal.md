---
layout: page
title: Installation with terminal/command prompt
permalink: /installation/terminal
---

### 3.1 CMake configuration with the command line
Navigate to the cloned NS3 folder, create a CMake cache folder, navigate to it and run [CMake](https://cmake.org/cmake/help/latest/manual/cmake.1.html) pointing to the NS3 folder.
```
cd NS3
mkdir cmake-cache
cd cmake-cache
cmake -DCMAKE_BUILD_TYPE=**look the tables below** -G"**look the tables below**" ..
```
You can pass arguments to the CMake command, to configure it.

To set the build type (debug or release) you will need to set the value of a variable (-D) named [CMAKE_BUILD_TYPE](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html) with the preset you want. You can choose one of the following:

| CMAKE_BUILD_TYPE | [Effects  (g++)](https://github.com/Kitware/CMake/blob/master/Modules/Compiler/GNU.cmake)  |
|:----------------:|:---------------:|
| DEBUG            | -g              |
| RELEASE          | -O3 -DNDEBUG    |
| RELWITHDEBINFO   | -O2 -g -DNDEBUG |
| MINSIZEREL       | -Os -DNDEBUG    |

You can also choose the generator for your preferred [buildsystem](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) with the following argument: -G "generator name (with double quotes)"

| Generators       | 
|:----------------:|
| MinGW Makefiles  | 
| Unix  Makefiles  | 
| MSYS  Makefiles  | 
| CodeBlocks - *one of the previous Makefiles* |
| Eclipse CDT4 - *one of the previous Makefiles* |
| Ninja            | 
| Xcode            |
| Visual Studio *VERSION* *YEAR* |

The Visual Studio generator also takes two flags to complete the build triplet.

| Function | CMake flag | Options |
|:--------:|:----------:|:-------:|
| Specify architecture | -A | x86,x64,x86_x64,x64_x86 |
| Specify tool chain | -T | ClangCL |

For specific ns-3 options, I recommend making a copy of the .cmake.template file and rename to .cmake, and then set the flags you want.
You could also edit NS3/CMakeLists.txt directly, but that's usually a bad idea.

You can also use an IDE that supports CMake projects.
Jetbrains CLion is the best one, but Visual Studio also exists for those who like it.
With both of them, you load the folder as a project, and they will look for the CMakeLists.txt file.

If the flag to automatically install dependencies is enabled, [VcPkg](https://github.com/Microsoft/vcpkg) will be used.
It is compiled and then downloads and build required dependencies during the first `cmake` run.
This can take quite some time.

The `cmake` command will be used in the future <del>, as it triggers the automatic copy of headers from NS3/src to /NS3/build/NS3</del>.
Update: The upstreamed cmake support only requires cmake refreshes to update targets and add new source files to them.

It is also used discover newer targets (libraries, executables and/or modules that were created since the last run).
This is known as reloading/updating the CMake cache.

## 3.2 Building the project with the command line
After the configuration, you will have multiple targets (for libraries and executables). Again, you can choose either command line tools or IDEs that support CMake projects to build and link those targets.

If you selected the Makefiles generator, you can run the `make` command to build specific targets and `make all` to build all targets.
You can also run `make clean` to remove built libraries and executables before rebuilding them.

## 3.3. Running built executables with the command line
After building executables, they will be placed in NS3/build/bin. To run them, you can either use the command line or your preferred IDE.

Navigate to NS3/build/bin and run the executable.
```
cd ../build/bin
./executable_name
```
If you want to rebuild it, you will need to navigate back to the cmake-cache folder.
```
cd ../../cmake-cache
```