
set(name csma)

set(source_files
        model/backoff.cc
        model/csma-channel.cc
        model/csma-net-device.cc
        helper/csma-helper.cc
        )

set(header_files
        model/backoff.h
        model/csma-channel.h
        model/csma-net-device.h
        helper/csma-helper.h
        )

#Set lib csma link dependencies
set(libraries_to_link ${libnetwork})

set(test_sources)

#Build csma lib
build_lib("${name}" "${source_files}" "${header_files}" "${libraries_to_link}" "${test_sources}")
