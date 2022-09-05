#pragma once

#include <vector>
#include <string>
#include <functional>
#include <algorithm>

std::vector<std::string> prefix_list = {
    " ",
    "\n",
};

std::vector<std::string> suffix_list = {
    " ",
    "\n",
};

namespace serfix {
    void subfix(std::string resource_character, int index_character, int token_keyword_length, std::function<void (bool, bool)> callback) {
        if(token_keyword_length < 1)
            return;

        std::string set_prefix(1, resource_character[index_character - 1]);
        std::string set_suffix(1, resource_character[index_character + token_keyword_length]);

        bool c_prefix = false;
        bool c_suffix = false;

        if(std::find(prefix_list.begin(), prefix_list.end(), set_prefix) != prefix_list.end()) {
            c_prefix = true;
        }

        if(std::find(suffix_list.begin(), suffix_list.end(), set_suffix) != suffix_list.end()) {
            c_suffix = true;
        }

        // std::cout << "PREFIX:" << set_prefix << " = " << c_prefix << std::endl;
        // std::cout << "SUFFIX:" << set_suffix << " = " << c_suffix << std::endl;

        callback(c_prefix, c_suffix);
    }
}