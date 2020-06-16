#include <string>

#include "PaulstretchLib.hpp"

namespace PaulstretchLib {

Configuration FromJSONString(const std::string&);
std::string JSONStringFromConfiguration(const Configuration&);

// new interface:

struct Configuration;
struct BatchTaskList;

struct JSONStringCodec{
    bool FromJSONString(Configuration&, const std::string&);
    bool FromJSONString(BatchTaskList&, const std::string&);
    
    std::string ToJSONString(const Configuration&);
    std::string ToJSONString(const BatchTaskList&);
    
};
};
