//
//  TextFileIO.cpp
//  sm620
//
//  Created by Alex on 12/06/2020.
//

#include "TextFileIO.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace PaulstretchLib {

const std::string TextFileIO::FromFile(const std::string& inName)
{
    std::string ret;

    std::ifstream in1(inName);
    std::ostringstream sstr;
    if (in1.rdbuf() == nullptr) {
        in1.close();

        return "";
    }
    sstr << in1.rdbuf();
    ret = sstr.str();
    in1.close();

    return ret;
}

const void TextFileIO::ToFile(const std::string& outName, const std::string& data)
{
    std::ofstream out1(outName);
    out1 << data;
    out1.close();
}
};
