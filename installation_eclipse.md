---
layout: page
title: Installation with Eclipse CDT
permalink: /installation/eclipse
---

### 3.0 Preparing Eclipse CDT
Start by downloading [Eclipse](https://www.eclipse.org/cdt/downloads.php).

Then unpack it and install the CMake plugins.

This can be done accessing the "Help->Install new software..."
![eclipse_install_software](/NS3/img/eclipse/install_software.png)
![eclipse_select_cmake_plugins](/NS3/img/eclipse/select_cmake_plugins.png)


### 3.1 Configuring ns-3 with the command line with Eclipse CDT

Configuring the project can be done either [directly via CMake](/NS3/installation/terminal) 
or via [ns3waf](NS3/installation/ns3waf).

For Eclipse we need the `-G"Eclipse CDT4 - Unix Makefiles"` generator, where `-G` is the flag
that allows us to specify the generator we want to use.

![cmake_configure_project](/NS3/img/eclipse/configure_project.png)

### 3.2 Opening the project with Eclipse CDT

Click to open the project folder
![open_project1](/NS3/img/eclipse/open_project_part_from_folder.png)

Specify the ns-3-dev folder (or whatever you have named it), it will take a while to scan and
will show both the top level project and the CMake cache folder.
![open_project2](/NS3/img/eclipse/load_project_part2.png)

The project will open and build targets will be listed on the right while sources are in the left.
![targets_and_indexer](/NS3/img/eclipse/build_target_and_indexer.png)

Auto-completion and other source-code related analysis take a while to begin working, 
while the C++ indexer runs (look at the bottom right of the window).

## 3.3 Building targets with Eclipse CDT

Select one of the targets, open the folders until you find a build target for that specific target.
The bottom panel will show the build progress.

![build_insights](/NS3/img/eclipse/build_finished_but_code_insights_still_missing.png)


### 3.4 Running executables with Eclipse CDT

Not sure if I missed something, but for now it is quite laborious to get these working.

First you click to create a new run target.
![create_run_target](/NS3/img/eclipse/create_new_run_target.png)

Then you choose the type of the target
![run_target_type](/NS3/img/eclipse/run_target_type.png)

Then you select the name of the target and path to the binary in ns-3-dev/build/.
![specify_binary](/NS3/img/eclipse/specify_binary_path_and_run_target_name.png)

This is quite bizarre since CLion, Xcode, Visual Studio, Code::Blocks and others do that automatically...

OK, now we select the run target in the dropdown menu on the top left or 
just click to run/debug and choose later.
![select_target_to_debug](/NS3/img/eclipse/select_target_to_debug.png)

Now we can set breakpoints and debug.
![debug_line_by_line](/NS3/img/eclipse/debug_line_by_line.png)

### Video covering all steps
<iframe width="560" height="315" src="https://www.youtube.com/embed/FLhHzEEDb00" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
