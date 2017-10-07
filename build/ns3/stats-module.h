#ifdef NS3_MODULE_COMPILATION
            # error "Do not include ns3 module aggregator headers from other modules these are meant only for end user scripts."
            #endif

            #ifndef NS3_MODULE_


            // Module headers:
                #include "file-helper.h"
                #include "gnuplot-helper.h"
                #include "data-calculator.h"
                #include "time-data-calculators.h"
                #include "basic-data-calculators.h"
                #include "data-output-interface.h"
                #include "omnet-data-output.h"
                #include "data-collector.h"
                #include "gnuplot.h"
                #include "average.h"
                #include "data-collection-object.h"
                #include "probe.h"
                #include "boolean-probe.h"
                #include "double-probe.h"
                #include "time-probe.h"
                #include "uinteger-8-probe.h"
                #include "uinteger-16-probe.h"
                #include "uinteger-32-probe.h"
                #include "time-series-adaptor.h"
                #include "file-aggregator.h"
                #include "gnuplot-aggregator.h"
                #include "get-wildcard-matches.h"
            #endif
            