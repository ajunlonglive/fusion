#pragma once

#include <phpcpp.h>

#include <fusion/error/message.cpp>
#include <fusion/regex/wrapper/pcre2.cpp>

class InputCapture : public Php::Base {
    public: void static is_capturable(std::string uri, std::string uri_route) {
        bool is_return = false;

        Php::out << uri_route << " = " << uri << std::endl << std::flush;

        std::string full_uri = "\\:" +uri;
        regexp::match(full_uri.c_str(), uri_route.c_str(), [&](const char *matched) {
            is_return = true;
        });

        std::string full_uri_regex = "\\:" +uri+ "\\:\\:\\(.*?\\)";
        regexp::match(full_uri_regex.c_str(), uri_route.c_str(), [&](const char *matched) {
            is_return = true;
        });

        if(!is_return)  
            Error::message::uncapturable_uri_input();
    }

    public: void static parse_input_capturable(std::string uri_route) {
        Php::out << "yes is capturable" << std::endl << std::flush;
    }
};