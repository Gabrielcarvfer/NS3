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


## 0. Configure your environment (Windows)

Wondering how to setup msys2 or WSL? [Check this link](/NS3/environment_setup_windows)


## 1. Getting the code
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

## 2. Creating a new module
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

After you finish working on your CMakeLists.txt, you need to refresh the cmake cache in order for it to be processed and targets available to build.

What the "cmake cache refresh" stands for will be clear in one of the next pages.

### For a shorter page and more direct information, instruction on how to configure, build and debug got separated.
- [Terminal/command line](/NS3/installation/terminal)
- [ns3waf: a waf-like wrapper for ns-3 with CMake](/NS3/installation/ns3waf)
- [JetBrains CLion](/NS3/installation/clion)
- [Microsoft Visual Studio](/NS3/installation/visualstudio)
- [Microsoft Visual Code](/NS3/installation/visualcode)
- [Apple Xcode](/NS3/installation/xcode)
- [Code::Blocks](/NS3/installation/codeblocks)
- [Eclipse CDT](/NS3/installation/eclipse)


