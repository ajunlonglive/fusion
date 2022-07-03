#pragma once

#include <phpcpp.h>

#include <fusion/error/message.cpp>
#include <fusion/regex/wrapper/pcre2.cpp>
#include <fusion/controllers/route/smart.h>

#include <vector>

class InputCapture : public Php::Base {
    public: void static is_capturable(std::string uri_subject, std::string uri_route) {
        bool is_return = false;
        std::vector<std::string> matched_uri;

        // Php::out << uri_route << " = " << uri << std::endl << std::flush;

        std::string full_uri = "\\:" +uri_subject+ "";

        // no conditional regex
        regexp::match(full_uri.c_str(), uri_route.c_str(), [&](const char *matched) {
            matched_uri.push_back(matched);
            is_return = true;
        });

        // with conditional regex
        std::string full_uri_regex = "\\:" +uri_subject+ "\\:\\:\\(.*?\\)";
        regexp::match(full_uri_regex.c_str(), uri_route.c_str(), [&](const char *matched) {
            matched_uri.push_back(matched);
            is_return = true;
        });

        if(!is_return)  
            Error::message::uncapturable_uri_input();
    }

    public: Php::Value static parse_input_capturable(std::string uri_subject, std::string uri_route) {
        std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"}); 

        std::vector<std::string> split_request_uri = SmartRouter::uri_route_split(request_uri, false);

        std::vector<std::string> split_uri_route = SmartRouter::uri_route_split(uri_route, false);
        
        // int orig_length_uri = split_request_uri.size();
        // int patt_length_uri = split_uri_route.size();
        
        Php::Value match_grouping;

        int iterate = 0;

        // if(orig_length_uri != patt_length_uri)
            // return 0;

        for(auto &uri_r : split_uri_route) {
            // regexp::match("^(?!:)[\\w+\\-\\:\\.\\_\\~\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\:\\@]*$", uri_r.c_str(), [&](const char * matched) {
            //     if(uri_r == split_request_uri[iterate]) {
                
            //     }
            // });

            regexp::match("(?<=^\\:)[\\w+_-]*$", uri_r.c_str(), [&](const char * matched) {
                match_grouping[matched] = split_request_uri[iterate];
            });

            regexp::match("(?<=^\\:)[\\w+_-]*(?=\\:\\:\\(.*?\\)$)", uri_r.c_str(), [&](const char * uname) {
                regexp::match("(?<=\\:\\:\\().*?(?=\\))", uri_r.c_str(), [&](const char * matched2) {
                    regexp::match(matched2, split_request_uri[iterate].c_str(), [&](const char * matched3) {
                        match_grouping[uname] = matched3;
                    });
                });
            });

            iterate++;
        }

        return match_grouping;
    }
};