//
//  TextFileIO.hpp
//
//  Created by Alex on 12/06/2020.
//

#ifndef TextFileIO_hpp
#define TextFileIO_hpp

#include <string>

namespace PaulstretchLib {
struct TextFileIO{
    static  const std::string FromFile(const std::string&);
    static const void ToFile(const std::string& fn, const std::string& data);
};
}

#endif /* TextFileIO_hpp */
