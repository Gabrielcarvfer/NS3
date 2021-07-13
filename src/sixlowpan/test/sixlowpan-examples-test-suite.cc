#include "ns3/example-as-test.h"

#ifndef CMAKE_EXAMPLE_AS_TEST
#define MODULE_PATH
#else
#define MODULE_PATH "./build/src/sixlowpan/examples/"
#endif

static ns3::ExampleAsTestSuite g_sixlowpanExample ("example-ping-lr-wpan", MODULE_PATH"example-ping-lr-wpan", NS_TEST_SOURCEDIR, "--disable-pcap --disable-asciitrace --enable-sixlowpan-loginfo");
