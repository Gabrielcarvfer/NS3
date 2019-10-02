//
// Created by Gabriel on 20-Nov-18.
//

#ifndef NS3_JSON_LOADER_H
#define NS3_JSON_LOADER_H

#include <ns3/picojson.h>
#include "../../../3rd-party/cpp-std-fwd/stdfwd.h"

picojson::object load_json(stdfwd::string jsonFile);

#endif //NS3_JSON_LOADER_H
