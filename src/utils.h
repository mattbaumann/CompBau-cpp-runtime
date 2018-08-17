#ifndef COMPBAU_CPP_RUNTIME_UTILS_H
#define COMPBAU_CPP_RUNTIME_UTILS_H

#include <algorithm>
#include <cctype>
#include <locale>

namespace runtime {

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
    }

    // trim from both ends (copying)
    static inline std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }
}

#endif //COMPBAU_CPP_RUNTIME_UTILS_H
