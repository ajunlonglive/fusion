#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

bool in_array(std::vector<std::string> array, std::string value) {
    return std::find(array.begin(), array.end(), value) != array.end() ? true : false;
}

bool array_key_exists(std::unordered_map<std::string, std::string> map, std::string key) {
    return map.find(key) != map.end() ? true : false;
}