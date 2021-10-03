---
layout: page
title: Installation with JetBrains CLion
permalink: /installation/clion
---

### 3.1 CMake configuration with CLion
CLion uses Makefiles for your platform as the default generator.

The following image contains the toolchain configuration for CLion running on Windows.
![toolchains](/NS3/img/clion/toolchains.png)

The following image contains the CMake configuration for CLion running on Windows.
Here you can choose a better generator like `ninja` by setting the cmake options flag to `-G Ninja`.

![configuration](/NS3/img/clion/cmake_configuration.png)

To reload the CMake cache, triggering the copy of new headers and discovery of new targets (libraries, executables and/or modules), you can either configure to re-run CMake automatically after editing CMake files (pretty slow and easily triggered) or reload manually. The following image shows how to trigger the CMake cache reload.
![reload_cache](/NS3/img/clion/reload_cache.png)

<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=61" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### 3.2 Building the project with CLion
You can select the desired target on a drop-down list and then click the hammer symbol, as shown in the image below.
![build_targets](/NS3/img/clion/build_targets.png)

### 3.3 Running executables with CLion
Select the desired target to run from the drop-down list and then click either: the play button to execute the program;
the bug to debug the program; the play button with a chip, to run Valgrind and analyze memory usage, leaks and so on.
![build_targets](/NS3/img/clion/run_target.png)

<iframe width="560" height="315" src="https://www.youtube.com/embed/db4-Zz5M3oA?start=338" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
