---
layout: page
title: Installation with Visual Code
permalink: /installation/visualcode
---

## 3.0 Install Visual Code

Start by downloading [VS Code](https://code.visualstudio.com/).

Then install it and then install the CMake and C++ plugins.

This can be done accessing the extensions' menu button on the left.
![cmake_tools](/NS3/img/vscode/install_cmake_tools.png)
![cpp_tools](/NS3/img/vscode/install_cpp_tools.png)

It will take a while, but it will locate the available toolchains for you to use.

## 3.1 Configuring ns-3 with Visual Code

It is literally just opening the ns-3-dev folder. It will run CMake automatically.
![open_project](/NS3/img/vscode/open_project.png)

After that, you can choose ns-3 features opening the CMake cache and toggling them on or off.
![open_cmake_cache](/NS3/img/vscode/open_cmake_cache.png)
![configure_ns3](/NS3/img/vscode/configure_ns3.png)

I'm going to enable examples now.
![enable_examples_and_save_to_reload_cache](/NS3/img/vscode/enable_examples_and_save_to_reload_cache.png)

Boom. Just like that cmake will run and update the targets on the left side 
of the screen in the CMake menu.

### 3.2 Building the project with VS Code

We can now select which target we want to build/debug on the left side menu.
I'm going to pick a random example and click to debug it. It will be built and debugging
will start right after that.
![select_target_build_and_debug](/NS3/img/vscode/select_target_build_and_debug.png)

While we wait for the compilation, lets appreciate the macro expansion feature.

![macro_expansion](/NS3/img/vscode/macro_expansion.png)

### 3.3 Running executables with VS Code

Select the target, right-click to choose to run or debug, like in the previous section.

After that, we can open the source file, put a few breakpoints and debug.

![happy_debugging](/NS3/img/vscode/happy_debugging.png)


### Video covering all steps
<iframe width="560" height="315" src="https://www.youtube.com/embed/Ab8eYHhT5I8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
