#include <string>

#include "PaulstretchLib.hpp"

namespace PaulstretchLib {

Configuration FromJSONString(const std::string&);
std::string JSONStringFromConfiguration(const Configuration&);

// new interface:

struct Configuration;
struct BatchTaskList;

struct JSONStringCodec{
    static bool FromJSONString(Configuration&, const std::string&);
    static bool FromJSONString(BatchData&, const std::string&);
    
    static std::string ToJSONString(const Configuration&);
    static std::string ToJSONString(const BatchData&);
    
};
};
