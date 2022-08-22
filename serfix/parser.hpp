#pragma once

#include <regex/wrapper/pcre2.hpp>

namespace serfix {
    class parse {
        public: std::string static code(std::string content) {
            std::string list_pattern;
            std::string list_replacement;
            std::string result = content;

            list_pattern += "(?<cd>(?<=cd)(\\s+|)(?<cdisi>(.*?))(?=\\;))|";
            list_replacement += "${cd:+ \\(${cdisi}\\)}";

            regexp::replace(list_pattern.c_str(), content.c_str(), list_replacement.c_str(), [&](const char *replaced) {
                result = replaced;
            });

            return result;
        }
    };
}