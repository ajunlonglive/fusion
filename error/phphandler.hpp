#pragma once

#include <phpcpp.h>
#include <iostream>

#include <regex/wrapper/pcre2.hpp>
#include <error/phphandler.hpp>

namespace Error {
    void PhpHandler(Php::Parameters &param) {
        int error_no             = param[0];
        std::string error_string = param[1];
        std::string error_file   = param[2];
        int error_line           = param[3];
        Php::Value error_context = param[4];

        Php::out << error_no << "<br />" << std::flush;
        Php::out << error_string << "<br />" << std::flush;
        
        std::string list_pattern = "(?<open>.*filename\\_)|(?<closed>\\+)";
        std::string list_replacement = "${open:+}${closed:+\\/}";

        regexp::replace(list_pattern.c_str(), error_file.c_str(), list_replacement.c_str(), [&](const char *replaced) {
            error_file = (std::string)replaced;
        });

        // Php::out << error_file << "<br />" << std::flush;
        Php::out << error_line << "<br />" << std::flush;
        Php::out << error_context << "<br />" << std::flush;
    }
}