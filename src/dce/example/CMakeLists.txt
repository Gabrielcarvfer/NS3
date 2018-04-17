set(header_files )

set(name udp-server)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name udp-client)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name udp-perf)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name tcp-server)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name tcp-client)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name tcp-loopback)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name unix-server)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name unix-client)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name udp-echo-server)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name udp-echo-client)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name dccp-server)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name dccp-client)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set( name freebsd-iproute)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libdce} ${libinternet})
build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

#set( name little-cout)
#set(source_files ${name}.cc)
#set(libraries_to_link ${libcore} ${libdce} ${libinternet})
#build_lib_example("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")



set(name dce-tcp-simple)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-udp-simple)
set(source_files ${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-ccnd-simple)
set(source_files ccnx/${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-ccnd-short-stuff)
set(source_files ccnx/${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-tap-udp-echo)
set(source_files ccnx/${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce} ${libtap-bridge} ${libpoint-to-point} ${libcsma})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-tap-ccnd)
set(source_files ccnx/${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce} ${libtap-bridge} ${libcsma})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-tap-vlc)
set(source_files ccnx/${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce} ${libtap-bridge} ${libcsma})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-ccn-cache)
set(source_files ccnx/${name}.cc ccnx/misc-tools.cc ccnx/misc-tools.h)
set(libraries_to_link ${libcore} ${libinternet} ${libdce} ${libpoint-to-point} ${libnetanim})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-bash-simple)
set(source_files bash/${name}.cc)
set(libraries_to_link ${libcore} ${libinternet} ${libdce})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-iperf)
set(source_files ${name}.cc ccnx/misc-tools.cc ccnx/misc-tools.h)
set(libraries_to_link ${libcore} ${libinternet} ${libdce} ${libpoint-to-point} ${libnetanim} ${libcsma})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name dce-iperf-emulation)
set(source_files ${name}.cc ccnx/misc-tools.cc ccnx/misc-tools.h)
set(libraries_to_link ${libcore} ${libinternet} ${libdce} ${libpoint-to-point} ${libnetanim} ${libcsma} ${libfd-net-device})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")

set(name linear-udp-perf)
set(source_files ${name}.cc) 
set(libraries_to_link ${libcore} ${libnetwork} ${libinternet} ${libdce} ${libpoint-to-point} ${libcsma} ${libapplications})
build_lib_example ("${name}" "${source_files}" "${header_files}" "${libraries_to_link}")
