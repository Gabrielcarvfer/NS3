---
layout: page
title: Installation with Visual Studio
permalink: /installation/visualstudio
---

### 3.1 CMake configuration with Visual Studio

#### 3.1.1 Visual C++ Compilers
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

#### 3.1.2 Linux Development (WSL)
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


#### 3.1.2.1 Remote Linux mode
If you choose remote linux for development, you can use either the GCC or Clang compilers. The default options offer debug and release with debug info configurations, or just use the pre-existing cache (e.g. configured with the command line/prompt). The remote linux option is quite slow, as the local development folder is constantly synced with the remote server using rsync. I suggest to scroll down and use WSL mode (next section).
![vs_wsl_setup_configuration_buildtype](/NS3/img/vs/vs_wsl_setup_configuration_remote_buildtype.png)

After confirming, you will be able to select your newly created configuration as a target.
![vs_wsl_setup_configuration_select_config](/NS3/img/vs/vs_wsl_setup_configuration_select_config.png)

Visual Studio will start syncing the local development folder with the remote server (in this case WSL). It will take a while.
![vs_wsl_setup_configuration_syncing](/NS3/img/vs/vs_wsl_setup_configuration_remote_syncing.png)


#### 3.1.2.2 WSL mode
If you use WSL mode, you can also choose between GCC or Clang compilers. Here the default options are debug and release (without debugging info), or a pre-existing cache (e.g. configured with the command line/prompt).
![vs_wsl_setup_configuration_buildtype](/NS3/img/vs/vs_wsl_setup_configuration_buildtype.png)

After confirming, you will be able to select your newly created configuration as a target. At this point a yellow banner should pop up on the top offering to install a customized CMake that supports the WSL/Visual Studio interaction.
![vs_wsl_setup_configuration_select_config](/NS3/img/vs/vs_wsl_setup_configuration_select_config.png)


#### 3.1.2.3 Target selection and ns-3 configuration through CMake options

Finally, you can select the CMake configurations for ns-3 and choose targets to build/debug, just like with native toolchains.
![vs_wsl_setup_cmake_options_and_targets](/NS3/img/vs/vs_wsl_setup_cmake_options_and_targets.png)

### 3.2 Building the project with Visual Studio
To select your target, you should switch from project files to projects view
in the solution explorer.
![vs_switch_to_targets](/NS3/img/vs/vs_switch_to_targets.png)

![vs_targets](/NS3/img/vs/vs_targets.png)

You can then click on either the play button or use the main Menu->Build->Build All.
![vs_build_debug_target](/NS3/img/vs/vs_build_debug_target.png)

![vs_build_project](/NS3/img/vs/vs_build_project.png)

