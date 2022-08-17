#pragma once

#include <phpcpp.h>

#include <database/core.hpp>
#include <regex/wrapper/pcre2.hpp> 
#include <error/message.hpp>      
#include <utils/string.hpp>

#include <functional>
#include <iostream>
#include <vector>
#include <regex>
#include <string>

class SmartRouter : public Php::Base {

    /**
     * @brief for private method under SmartRouter class, used for utils/helper each worker method for each purpose
     */
    public: void static boot(std::function<void()> callback) {
        Php::Value web_route_list = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"});
        if(Php::count(web_route_list) > 0) {
            callback();
        }
    }

    public: void static regist(std::string uri_route) {
        regexp::replace("(?<non>(?<=\\/)\\:(?!\\:).*?(?=\\/))|(?<regex>\\:\\:.*?\\()|(?<close>\\)(?=\\/))", uri_route.c_str(), "${non:+.*}${regex:+}${close:+}", [&](const char *replaced) {
            Database::set::push_array_string({"FUSION_STORE" "FS_ROUTE", "FS_Web_Route_Identics_List"}, (std::string)replaced);
        });        

    }

    public: void static validate(std::string uri_route, std::string request_uri, bool *address_allowed) {
        bool result = false;
        const char *filtered_uri_route = uri_route.c_str();

        regexp::match(filtered_uri_route, request_uri.c_str(), [&](const char *matched) {
            Database::set::push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Param"}, filtered_uri_route);
            result = true;
        });

        if(Php::count(Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Param"})) > 1) {
            Error::message::match_uri_identics();
        }

        *address_allowed = result;
    }

    /**
     * @brief a god/main function, used for running flow a SmartRoute idiomatic.
     */
    public: bool static run(std::string uri_route, std::string request_uri, bool use_filter) {
        boot([&](){
            Php::Value filtered_identics_list = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_List"});
            for(auto &route : filtered_identics_list) {
                Php::out << route.second << "<br />" << std::flush;
            }
        });

        return true;
    }
};