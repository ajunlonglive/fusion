#pragma once

#include <phpcpp.h>
#include <regex>


namespace Regex {
    class uri : public Php::Base {
        public: std::string static escape_request_uri(std::string uri_route) {
            std::regex reg("\\/\\/*\\/");
            std::string uri_route_filtered = regex_replace(uri_route, reg, "/");

            return uri_route_filtered;
        }
    };
}