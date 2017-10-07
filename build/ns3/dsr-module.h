#ifdef NS3_MODULE_COMPILATION
            # error "Do not include ns3 module aggregator headers from other modules these are meant only for end user scripts."
            #endif

            #ifndef NS3_MODULE_


            // Module headers:
                #include "dsr-routing.h"
                #include "dsr-options.h"
                #include "dsr-fs-header.h"
                #include "dsr-option-header.h"
                #include "dsr-maintain-buff.h"
                #include "dsr-passive-buff.h"
                #include "dsr-rsendbuff.h"
                #include "dsr-rcache.h"
                #include "dsr-rreq-table.h"
                #include "dsr-gratuitous-reply-table.h"
                #include "dsr-errorbuff.h"
                #include "dsr-network-queue.h"
                #include "dsr-helper.h"
                #include "dsr-main-helper.h"
            #endif
            