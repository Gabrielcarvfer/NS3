//
// Created by Gabriel on 14-Nov-18.
//
#include <ns3/picojson.h>
#include <iostream>
#include <fstream>
#include <sstream>

picojson::object load_json(std::string jsonFile)
{
    //File and content manipulator
    std::ifstream errorDataFile;
    std::stringstream ss;

    //Read input file
    errorDataFile.open(jsonFile, std::ios::binary);
    ss << errorDataFile.rdbuf();
    errorDataFile.close();

    //Parse input
    picojson::value v;
    ss >> v;
    std::string err = picojson::get_last_error();
    if (!err.empty())
    {
        std::cerr << err << std::endl;
        exit(-1);
    }

    //Return json object
    picojson::object &o = v.get<picojson::object>();
    return o;
}

