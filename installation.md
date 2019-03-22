---
layout: page
title: Installation
permalink: /installation
---
## 0. Download, build and debug ns-3 with CMake 

Assumes pre-existing toolchain and pre-configured environment.
Remember to enable the subtitles.

<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## 1. Pre-requisites

### 1.1 Toolchain
Before proceeding you will need: 

    1. git
    2. g++ (>=7 for VcPkg)
    3. make or ninja
    4. cmake
    5. unzip
    6. curl 
    7. tar
    8. pkg-config (for VcPkg on Linux)
    
Those are basic pre-requisites for both ns-3 and VcPkg, used in this version of ns-3 for dependencies installation. The [official ns-3 branch](https://gitlab.com/nsnam/ns-3-dev/) uses Bake for dependencies installation.

For package-manager commands used to install these packages, look at `Install required packages` entries in the [CI file](https://github.com/Gabrielcarvfer/NS3/blob/master/.github/workflows/per_commit.yml).

### 1.2 Configure the environment

#### 1.2.1 Msys2
Msys2 offers a ton of Unix/Posix tools on Windows. To install it, first go to [MSYS2 page](https://www.msys2.org/), download and run the installer.
After that you can change the path in buildsupport/macros_and_definitions.cmake. Or make our life easier and add `DRIVE_LETTER:\\path_where_you_installed_msys\\msys64\\mingw64\\bin` folder to your PATH. 

#### 1.2.2 WSL

#### 1.2.2.1 Important info about WSL
WSL is awesome (the v1, v2 is just a glorified VM managed by MSFT). You can have both versions simultaneously, but that is really unnecessary.
Before telling you the WSL page, I must inform you that you should read the rest of this section before installing anything.

When installing WSLv1, you won't need to enable the Virtual Machine Platform (VM support in MSFT speak). 
Pros: you can see linux processes on Windows task manager, enabling VM support makes Windows run on top of the Hypervisor (Hyper-V), which in turn prevents the host OS (a.k.a. Windows) from accessing a ton of performance counters (used by AMD uProf, Intel V-Tune and others). 
Cons: [filesystem performance is trash](https://github.com/microsoft/WSL/issues/873), [long doubles are 64 bit instead of 80 bit](https://github.com/microsoft/WSL/issues/830), Qt and other libraries may have [an ABI section which is not parsed correctly](https://github.com/microsoft/WSL/issues/3023) and cause issues, [stack execution is prohibited](https://github.com/microsoft/WSL/issues/2553#issuecomment-335201548), etc.

If you want to use WSLv1 without having to install the Virtual Machine garbo, first enable WSL and then run `wsl --set-default-version 1` on the command prompt with administrative rights. That will prevent distributions from trying to use WSLv2, which will require you to install Virtual Machine Platform to finish installation and then allow you to migrate to WSLv1.

WSLv2 on the other hand is a glorified VM running on top of the Hypervisor (not Windows).
If you access stuff from WSL mounts (e.g. `/mnt/c/Users/Gabriel/Desktop`) you have [even worse performance than in WSLv1](https://github.com/microsoft/WSL/issues/4197).
This is why I still use v1 and will continue to do so. If you put your code inside the VM, performance is near baremetal. 

#### 1.2.2.2 Installing WSL

You can enable WSL by clicking checkboxes in "Turn Windows Features on or off".
![wsl_feature](/NS3/img/wsl_feature.png)

Or you can use the command line/prompt. For WSLv1 and WSLv2 you will need to run the following command as an administrator.
```
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

If you're installing WSLv2, make sure to enable the "Virtual Machine Platform" and "Windows Subsystem for Linux" in your control panel (or through command line).
```
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

WSLv2 requires an additional package with the Linux Kernel, that Microsoft started shipping separately from Windows. You can find it [here](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi). Same link can be found in their official page, but I'm color blind and the link was not immediately clear.

In case of trouble, look at the [WSL official installation page](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

#### 1.2.2.3 Setting up WSL for development

I usually use Jetbrains CLion, and they wrote [instructions](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html) and a [litte script that setups everything automagically](https://raw.githubusercontent.com/JetBrains/clion-wsl/master/ubuntu_setup_env.sh).

Just configure CLion to use WSL and enter your SSH port (2222 in their script), username and password.

If you're interested in GUI applications running inside WSL (e.g. NetAnim), you can install a X11 server on Windows (e.g. [VcxSrv](https://sourceforge.net/projects/vcxsrv/files/latest/download)) and redirect your WSL applications to it.

To redirect GUI application to the X11 server on Windows, add the following to the last line of `~/.bashrc`:
- For WSLv1: `DISPLAY=:0`
- For WSLv2: `DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0`

To run the VcxSrv after each reboot, either search for `Task Scheduler` and create a task manually to run every boot and login with
 - Command: `"C:\Program Files\VcXsrv\vcxsrv.exe"`
 - Arguments: `:0 -ac -terminate -lesspointer -multiwindow -clipboard -wgl`

Or download [this XML](https://raw.githubusercontent.com/Gabrielcarvfer/WSLSetup/master/VcxSrv.xml) and run the following with administrative priviledges:
```
schtasks /create /TN "VcxSrv" /XML ".\VcxSrv.xml"
schtasks /Run /TN "VcxSrv"
```



## 2. Getting the code
After installing the dependencies, clone the [ns-3 with CMake](https://github.com/Gabrielcarvfer/NS3) repository. 
```
git clone https://github.com/Gabrielcarvfer/NS3.git
```

You can use shallow clone to speed things up (by cloning the mostly up-to-date branch).
```
git clone --branch master --single-branch https://github.com/Gabrielcarvfer/NS3.git
```
or by dropping the entire git history
```
git clone --depth 1 https://github.com/Gabrielcarvfer/NS3.git
```

## 3. CMake configuration 
You can choose either command line tools or IDEs that support CMake projects (e.g. [Jetbrains CLion](https://www.jetbrains.com/clion/) and [Visual Studio](https://visualstudio.microsoft.com/) ).


### 3.1 CMake configuration with command line 
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

The `cmake` command will be used in the future, as it triggers the automatic copy of headers from NS3/src to /NS3/build/NS3.
It is also used discover newer targets (libraries, executables and/or modules that were created since the last run). 
This is known as reloading/updating the CMake cache.

### 3.2 CMake configuration with CLion
CLion uses Makefiles for your platform as the default generator. 

The following image contains the toolchain configuration for CLion running on Windows.
![toolchains](/NS3/img/toolchains.png)

The following image contains the CMake configuration for CLion running on Windows. 
Here you can choose a better generator like `ninja` by setting the cmake options flag to `-G Ninja`.

![configuration](/NS3/img/cmake_configuration.png)

To reload the CMake cache, triggering the copy of new headers and discovery of new targets (libraries, executables and/or modules), you can either configure to re-run CMake automatically after editing CMake files (pretty slow and easily triggered) or reload manually. The following image shows how to trigger the CMake cache reload.
![reload_cache](/NS3/img/reload_cache.png)

<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=61" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### 3.3 CMake configuration with Visual Studio

#### 3.3.1 Visual C++ Compilers
Visual Studio is cursed and uses nmake/msbuild as generators.
Start by opening the folder as a project.
![vs_open_project](/NS3/img/vs/vs_open_folder_as_project.png)

Then right-click the CMakeLists.txt file and click to generate the cmake cache.
![vs_generate_cache](/NS3/img/vs/vs_generate_cmake_cache.png)

REMINDER: Only ClangCl is supported. You must open the cmake configuration panel that Visual Studio provides,
look for advanced settings and select the appropriate clangcl toolchain. It won't build with the MSVC (cl.exe) compiler.
![vs_change_cmake_settings](/NS3/img/vs/vs_change_cmake_settings.png)
![vs_set_clang_toolchain](/NS3/img/vs/vs_set_clang_toolchain.png)

Visual Studio should regenerate the caches after that.

#### 3.3.2 Linux Development (WSL)
If you want to use this feature, make sure to enable the Linux development feature during Visual Studio installation.
![wsl_visual_studio](/NS3/img/vs/wsl_visual_studio.png)

After that open the folder containing the CMake project.
![vs_wsl_target](/NS3/img/vs/vs_wsl_target.png)

It will show a list of stuff to do (install the Visual Studio package I've mentioned, along with WSL). After that you will need to setup a SSH connection (I recommend to follow the Jetbrains [instructions](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html) mentioned in the WSL section).
![vs_wsl_setup](/NS3/img/vs/vs_wsl_setup.png)

When you click to open the Connection Manager, a window will open. Then you need to `add` a new entry with your WSL credentials.
![vs_wsl_setup_credentials](/NS3/img/vs/vs_wsl_setup_credentials.png)

When you're done and close the credentials window, the connection will be listed.
![vs_wsl_setup_credentials_ok](/NS3/img/vs/vs_wsl_setup_credentials_ok.png)

After that, click the `add a new configuration` button, to add the WSL as a Visual Studio target.
![vs_wsl_setup_configuration](/NS3/img/vs/vs_wsl_setup_configuration.png)


#### 3.3.2.1 Remote Linux mode
If you choose remote linux for development, you can use either the GCC or Clang compilers. The default options offer debug and release with debug info configurations, or just use the pre-existing cache (e.g. configured with the command line/prompt). The remote linux option is quite slow, as the local development folder is constantly synced with the remote server using rsync. I suggest to scroll down and use WSL mode (next section).
![vs_wsl_setup_configuration_buildtype](/NS3/img/vs/vs_wsl_setup_configuration_remote_buildtype.png)

After confirming, you will be able to select your newly created configuration as a target.
![vs_wsl_setup_configuration_select_config](/NS3/img/vs/vs_wsl_setup_configuration_select_config.png)

Visual Studio will start syncing the local development folder with the remote server (in this case WSL). It will take a while.
![vs_wsl_setup_configuration_syncing](/NS3/img/vs/vs_wsl_setup_configuration_remote_syncing.png)


#### 3.3.2.2 WSL mode
If you use WSL mode, you can also choose between GCC or Clang compilers. Here the default options are debug and release (without debugging info), or a pre-existing cache (e.g. configured with the command line/prompt).
![vs_wsl_setup_configuration_buildtype](/NS3/img/vs/vs_wsl_setup_configuration_buildtype.png)

After confirming, you will be able to select your newly created configuration as a target. At this point a yellow banner should pop up on the top offering to install a customized CMake that supports the WSL/Visual Studio interaction.
![vs_wsl_setup_configuration_select_config](/NS3/img/vs/vs_wsl_setup_configuration_select_config.png)


#### 3.3.2.3 Target selection and ns-3 configuration through CMake options

Finally, you can select the CMake configurations for ns-3 and choose targets to build/debug, just like with native toolchains.
![vs_wsl_setup_cmake_options_and_targets](/NS3/img/vs/vs_wsl_setup_cmake_options_and_targets.png)


## 4 Building the project
After the configuration, you will have multiple targets (for libraries and executables). Again, you can choose either command line tools or IDEs that support CMake projects to build and link those targets.


### 4.1 Building the project with command line
If you selected the Makefiles generator, you can run the `make` command to build specific targets and `make all` to build all targets.
You can also run `make clean` to remove built libraries and executables before rebuilding them.

### 4.2 Building the project with CLion
You can select the desired target on a drop-down list and then click the hammer symbol, as shown in the image below.
![build_targets](/NS3/img/build_targets.png)

### 4.3 Building the project with Visual Studio
To select your target, you should switch from project files to projects view
in the solution explorer.
![vs_switch_to_targets](/NS3/img/vs/vs_switch_to_targets.png)

![vs_targets](/NS3/img/vs/vs_targets.png)

You can then click on either the play button or use the main Menu->Build->Build All.
![vs_build_debug_target](/NS3/img/vs/vs_build_debug_target.png)

![vs_build_project](/NS3/img/vs/vs_build_project.png)

### 4.4 Configuring ns-3 with the command line and building the project with Code::Blocks
<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=590" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### 4.5 Configuring ns-3 with the command line and building the project with Xcode
<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=1230" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## 5. Running built executables
After building executables, they will be placed in NS3/build/bin. To run them, you can either use the command line or your prefered IDE.

### 5.1 Running executables with command line
Navigate to NS3/build/bin and run the executable.
```
cd ../build/bin
./executable_name
```
If you want to rebuild it, you will need to navigate back to the cmake-cache folder.
```
cd ../../cmake-cache
```

### 5.2 Running executables with CLion
Select the desired target to run from the drop-down list and then click either: the play button to execute the program;
the bug to debug the program; the play button with a chip, to run Valgrind and analyze memory usage, leaks and so on.
![build_targets](/NS3/img/run_target.png)

<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=338" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### 5.3 Running executables with Code::Blocks
<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=899" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### 5.4 Running executables with Xcode
<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=1396" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## 6. Creating a new module
As [Waf](https://waf.io/) (the official buildsystem) was replaced with CMake, the required steps to create a new module for the ns-3 change slightly.

Instead of a wscript per module, you will need a CMakeLists.txt file. As an example, let's take the Applications module wscript and compare to the CMakeLists.txt that replaced it.

### Applications Wscript
```
def build(bld):
    module = bld.create_ns3_module('applications', ['internet', 'config-store','stats'])
    module.source = [
        'model/bulk-send-application.cc',
        ...
        ]

    applications_test = bld.create_ns3_module_test_library('applications')
    applications_test.source = [
        'test/three-gpp-http-client-server-test.cc', 
        ...
        ]

    headers = bld(features='ns3header')
    headers.module = 'applications'
    headers.source = [
        'model/bulk-send-application.h',
        ...
        ]
```

### Applications CMakeLists.txt
```


set(name applications)

set(source_files
        model/bulk-send-application.cc
        ...
        )

set(header_files
        model/bulk-send-application.h
        ...
        )

#link to dependencies
set(libraries_to_link
        ${libinternet}
        ${libconfig-store}
        ${libstats}
        )

set(test_sources
        test/udp-client-server-test.cc
        ...
    )

build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
```

After you finish working on your CMakeLists.txt, add your new module to the libs_to_build list in the NS3/CMakeLists.txt file.

Reconfigure your CMake project (step 3) to automatically copy the headers to NS3/build/NS3 and create the appropriate buildsystem files to build your module related targets.
