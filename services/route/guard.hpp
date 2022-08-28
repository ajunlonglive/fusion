#pragma once

#include <phpcpp.h>

#include <transport/session/session.hpp>
// #include <database/redis.hpp>
#include <regex/wrapper/pcre2.hpp> 
#include <error/message.hpp>      
#include <utils/string.hpp>

#include <functional>
#include <iostream>
#include <vector>
#include <regex>
#include <string>


namespace services {
    namespace route {


class c_guard : public Php::Base {

    /**
     * @brief for private method under SmartRouter class, used for utils/helper each worker method for each purpose
     */
    public: void static m_boot(std::function<void()> callback) {
        Php::Value web_route_list = transport::session::c_get::m_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Lists"});
        if(Php::count(web_route_list) > 0) {
            callback();
        }
    }

    public: void static m_permist_step_mode() {
            transport::session::c_set::m_boolean({"FUSION_STORE", "FS_ROUTE", "Permist_Step"}, true);
    }

    public: bool static m_regist(std::string uri_route, bool permist_step) {
        if(!permist_step) {
            Php::Value double_v_check = transport::session::c_get::m_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Lists"});

            if(double_v_check[uri_route])
                Error::message::v_double_uri();

            const char *result = uri_route.c_str();
            
            regexp::replace("(?<non>(?<=\\/)\\:(?!\\:).*?(?=\\/))|(?<regex>\\:\\:.*?\\()|(?<close>\\)(?=\\/))", uri_route.c_str(), "${non:+[\\\\w+\\\\-\\:\\.\\_\\~\\!\\$\\&\\\\'\\(\\)\\*\\+\\\\,\\;\\=\\:\\@\\\\[\\\\]]*}${regex:+}${close:+}", [&](const char *replaced) {
                result = replaced;
            }); 

            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Lists", uri_route}, (std::string)result);  
        }

        return permist_step;
    }

    public: bool static m_validate(std::string filt_uri_route, std::string orig_uri_route, std::string request_uri) {
        bool result = false;
        std::string prefix = "^" + filt_uri_route + "$";
        const char *filtered_uri_route = prefix.c_str();

        // Match the uri decorator
        regexp::match(filtered_uri_route, request_uri.c_str(), [&](const char *matched) {
            transport::session::c_set::m_push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Param"}, filtered_uri_route);
            result = true;
        });
        
        return result;
    }

    /**
     * @brief a god/main function, used for running flow a SmartRoute idiomatic.
     */
    public: void static m_run() {
        m_boot([&](){

            Php::Value filtered_identics_list = transport::session::c_get::m_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Lists"});
            for(auto& root : filtered_identics_list) {
                for(auto& pair : filtered_identics_list) {
                    
                    if(root.first == pair.first) continue;

                    if(root.second != pair.second) {
                        std::string root_f = "^" + (std::string)root.second + "$";
                        std::string pair_f = pair.second;

                        regexp::match(root_f.c_str(), pair_f.c_str(), [&](const char *matched) {
                            Error::message::match_uri_identics();
                        });
                    } else {
                        Error::message::match_uri_identics();
                    }

                    // Step for indentification same/indentics param placeholder
                    std::string orig_uri_route = root.first;
                    std::vector<std::string> orig_uri_route_split = utils::str_split("/", orig_uri_route.substr(1, orig_uri_route.length() - 2) );
                    std::vector<std::string> parsed_uri;

                    for(auto &orig_per : orig_uri_route_split) {
                        regexp::match("(?<=^\\:\\:)[\\w+_-]*(?=\\()|(?<=^\\:)[\\w+_-]*$", orig_per.c_str(), [&](const char *matched) {
                            parsed_uri.push_back((std::string)matched);
                        });
                    }

                    if(std::adjacent_find(parsed_uri.begin(), parsed_uri.end()) != parsed_uri.end()) {
                        Error::message::param_uri_identics();
                    }
                                        
                }
            }

        });
    }
};


    }
}