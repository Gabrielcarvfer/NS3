# Find C++ header files that are slow to compile

This repo contains a simple tool to find which headers take the
longest time to parse for any given input file. To see it in action,
cd to the root of this repository and issue the following commands:

```shell
meson build
cd build
ninja
../slowfinder.py ../prog.cpp
```

The code has been tested with Meson but it should work with any build
system that produces a `compile_commands.json` database.
