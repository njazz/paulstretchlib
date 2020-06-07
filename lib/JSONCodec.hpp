#include <string>

#include "PaulstretchLib.hpp"

namespace PaulstretchLib {

Configuration FromJSONString(const std::string&);
std::string JSONStringFromConfiguration(const Configuration&);

};
