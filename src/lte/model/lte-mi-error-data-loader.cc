//
// Created by Gabriel on 14-Nov-18.
//

#include <ns3/picojson.h>
#include <iostream>
#include <fstream>
#include <sstream>

int loadErrorData()
{
    //File and content manipulator
    std::ifstream errorDataFile;
    std::stringstream ss;

    //Read input file
    errorDataFile.open("../../src/lte/model/errorData.min.json", std::ios::binary);
    ss << errorDataFile.rdbuf();
    errorDataFile.close();

    std::cout << ss.str() << std::endl;
    //Parse input
    picojson::value v;
    ss >> v;
    std::string err = picojson::get_last_error();
    if(!err.empty()) {
        std::cerr << err << std::endl;
        return -1;
    }

    picojson::object& o = v.get<picojson::object>();

    picojson::array& aAry = o["BlerCurvesEcrMap"].get<picojson::array>();
    std::cout << "TestAry:" << std::endl;
    for (long long i = 0; i < aAry.size(); i++)
        std::cout << "\t" << aAry[i].get<double>() << std::endl;
    return 0;
}

int main()
{
    return loadErrorData();
}