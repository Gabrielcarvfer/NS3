set(name netsimulyzer)

set(source_files
        helper/building-configuration-container.cc
        helper/building-configuration-helper.cc
        helper/node-configuration-container.cc
        helper/node-configuration-helper.cc
        model/node-configuration.cc
        model/building-configuration.cc
        model/category-axis.cc
        model/category-value-series.cc
        model/color.cc
        model/decoration.cc
        model/log-stream.cc
        model/netsimulyzer-version.cc
        model/orchestrator.cc
        model/rectangular-area.cc
        model/series-collection.cc
        model/state-transition-sink.cc
        model/value-axis.cc
        model/xy-series.cc
        model/throughput-sink.cc
        )

set(header_files
        helper/building-configuration-container.h
        helper/building-configuration-helper.h
        helper/node-configuration-container.h
        helper/node-configuration-helper.h
        library/json.hpp
        model/event-message.h
        model/log-stream.h
        model/netsimulyzer-3D-models.h
        model/netsimulyzer-version.h
        model/node-configuration.h
        model/optional.h
        model/building-configuration.h
        model/category-axis.h
        model/category-value-series.h
        model/color.h
        model/color-palette.h
        model/decoration.h
        model/orchestrator.h
        model/rectangular-area.h
        model/series-collection.h
        model/state-transition-sink.h
        model/value-axis.h
        model/xy-series.h
        model/throughput-sink.h
        )

set(libraries_to_link
        ${libbuildings}
        ${libcore}
        ${libnetwork}
        ${libmobility}
        )

set(test_sources
        )

set(original_cxx_standard ${CMAKE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD 17)

build_contrib_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")

set(CMAKE_CXX_STANDARD ${original_cxx_standard})
