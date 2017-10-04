NS3_common_includes()

set(name config-store)
set(lib${name} ns${NS3_VER}-${name}-${build_type})
add_library(${lib${name}} SHARED
        model/attribute-default-iterator.cc
        model/attribute-default-iterator.h
        model/attribute-iterator.cc
        model/attribute-iterator.h
        model/config-store.cc
        model/config-store.h
        model/display-functions.cc
        model/display-functions.h
        model/file-config.cc
        model/file-config.h
        model/gtk-config-store.cc
        model/gtk-config-store.h
        model/model-node-creator.cc
        model/model-node-creator.h
        model/model-typeid-creator.cc
        model/model-typeid-creator.h
        model/raw-text-config.cc
        model/raw-text-config.h
        model/xml-config.cc
        model/xml-config.h
        )

#set(test${name} ns${NS3_VER}-${name}-test-${build_type})
#add_library(${test${name}} SHARED)

