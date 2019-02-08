//
// Created by Gabriel on 20-Nov-18.
//

#ifndef NS3_JSON_LOADER_H
#define NS3_JSON_LOADER_H

#include <ns3/picojson.h>
#include <iostream>
#include <fstream>
#include <sstream>

picojson::object load_json(std::string jsonFile);

#endif //NS3_JSON_LOADER_H
