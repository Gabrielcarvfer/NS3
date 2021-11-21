---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---

The [ns-3 with CMake](https://github.com/Gabrielcarvfer/NS3) project is a modified version of the original [NSNAM ns-3](https://www.nsnam.org/) network simulator. 

The main changes are related to the buildsystem, replacing the original Waf with CMake, for the sake of using [Jetbrains CLion](https://www.jetbrains.com/clion/). 
In addition to Linux and MacOS, Windows is supported with both MinGW/Msys2 and ClangCL/MSVC (WIP, don't use it for real work yet).

Most ns-3 features are already usable with CMake, but python bindings and visualizer are still not working.

Instructions on how to work with it are available in the [installation page](/NS3/installation)

If you are looking for the collaborative sensing adaptations for the ns-3 LTE module, check the [ns-3-COLAB page](/NS3/COLAB), or the [COLAB-5G](/NS3/COLAB-5G) for additional rural 5G adaptations.

If you are looking for the 802.11 AP with the dynamic beacon adjustment, check out the [ns-3-dynamicBeacon page](/NS3/dynamicBeacon)

You can find me on the [official NSNAM Zulip server](ns-3.zulipchat.com).
