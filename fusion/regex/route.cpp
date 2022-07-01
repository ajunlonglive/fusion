#pragma once

#include <phpcpp.h>
#include <regex>


namespace Regex {
    class uri : public Php::Base {
        public: std::string static escape_request_uri(std::string uri_route) {
            std::string escape_backslash_uri = std::regex_replace(uri_route, std::regex("\\/\\/*\\/"), "/");
            std::string uri_route_filtered = std::regex_replace(escape_backslash_uri, std::regex("\\\\"), "$fs_bs$");
            return uri_route_filtered;
        }
    };
}