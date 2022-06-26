#pragma once

#include <phpcpp.h>

#include <regex>

class InputCapture : public Php::Base {
    public: void static is_capturable(std::string uri_route) {
            Php::out << uri_route << std::flush;
        if(std::regex_search(uri_route, std::regex("(\\/\\:)\\w+(?=\\/)"))) {
            Php::out << uri_route << std::flush;
            Php::out << "true" << std::flush;
        } else {
            Php::out << uri_route << std::flush;
            Php::out << "false1" << std::flush;
        }
    }
};