#ifdef NS3_MODULE_COMPILATION 
    error "Do not include ns3 module aggregator headers from other modules these are meant only for end user scripts." 
#endif 
#ifndef NS3_MODULE_BUILDINGS
    // Module headers: 
    #include "building.h"
    #include "building-list.h"
    #include "mobility-building-info.h"
    #include "itu-r-1238-propagation-loss-model.h"
    #include "buildings-propagation-loss-model.h"
    #include "hybrid-buildings-propagation-loss-model.h"
    #include "oh-buildings-propagation-loss-model.h"
    #include "building-container.h"
    #include "building-allocator.h"
    #include "building-position-allocator.h"
    #include "buildings-helper.h"
#endif 