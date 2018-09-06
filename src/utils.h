#ifndef COMPBAU_CPP_RUNTIME_UTILS_H
#define COMPBAU_CPP_RUNTIME_UTILS_H

#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>
#include <iterator>

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

    /// \brief Joins any datatype together and inserts the separator between.
    ///
    /// This function requires your type to have an output operator which writes the types into an underlaying string.
    template<typename FwdIter>
    std::string join(FwdIter begin, FwdIter end, std::string const &separator) {
        std::ostringstream builder{};
        using item_type = typename std::iterator_traits<FwdIter>::value_type;
        std::copy(begin, end, std::ostream_iterator<item_type>{builder, separator.c_str()});
        auto joined = builder.str();
        return joined.substr(0, joined.size() - separator.size());
    }
}

#endif //COMPBAU_CPP_RUNTIME_UTILS_H
