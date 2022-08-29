#pragma once

#include <vector>
#include <string>

namespace utils {
    namespace string {
    

std::vector<std::string> f_str_split(std::string separate, std::string a_string) {
    std::vector<std::string> tmp = {""};

    for(auto &e : a_string) {
        if(std::string(1, e) != separate) {
            tmp[tmp.size() - 1] += e;
        } else {
            tmp.push_back("");
        }
    }

    return tmp;
}

void f_replace_all(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


    }
}