//
//  StringUtilities.cpp
//  nseq-core-library
//
//  Created by Alex on 18/07/2018.
//  Copyright © 2018 Alex Nadzharov. All rights reserved.
//

#ifndef StringUtilities_hpp
#define StringUtilities_hpp

#include <string>
#include <vector>

namespace StringUtilities {

    static inline std::vector<std::string> SplitStringWithDelimiter(const std::string& str,const std::string& delimiter)
    {
        auto str0= str;
        std::vector<std::string> tokens;
        size_t pos = 0;
        while ((pos = str0.find(delimiter)) != std::string::npos) {
            
            tokens.push_back(str0.substr(0, pos));
            str0.erase(0, pos + delimiter.length());
        }

        tokens.push_back(str0);
        return tokens;
    }

   static inline  std::string JoinStringsWithDelimiter(const std::vector<std::string>& vec, const std::string& delim)
    {
        std::string ret = "";
        
        if (vec.size() == 1)
            return vec[0];

        unsigned int i = 0;
        for (auto s : vec) {

            //if (s != "")
            ret += s;
            if (i != vec.size() - 1)
                ret += delim;

            i++;
        }
        return ret;
    }

   static inline std::string ReplaceTokenInString(const std::string& src, const std::string& src_token, const std::string& dest_token)
    {
        return JoinStringsWithDelimiter(SplitStringWithDelimiter(src, src_token), dest_token);
    }

    static inline std::string EscapeJSONString(const std::string& src)
    {
        std::string ret;

        ret = ReplaceTokenInString(ret, "\\", "\\\\");
        ret = ReplaceTokenInString(src, "\"", "\\\"");
        ret = ReplaceTokenInString(ret, "\n", "\\n");
        ret = ReplaceTokenInString(ret, "\t", "\\t");

        return ret;
    }

    static inline std::string UnescapeJSONString(const std::string& src)
    {
        std::string ret;

        ret = ReplaceTokenInString(ret, "\\\\", "\\");
        ret = ReplaceTokenInString(src, "\\\"", "\"");
        ret = ReplaceTokenInString(ret, "\\n", "\n");
        ret = ReplaceTokenInString(ret, "\\t", "\t");

        return ret;
    }
    
    static inline bool StartsWith(const std::string& src, const std::string& m){
        return !src.substr(0, m.size()).compare(m);
    }

};

#endif
