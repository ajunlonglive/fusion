#pragma once

#include <phpcpp.h>

#include <fusion/database/core.cpp>
#include <fusion/regex/wrapper/pcre2.cpp> 
#include <fusion/error/message.cpp>      

#include <fusion/utils/string.h>

#include <iostream>
#include <vector>
#include <regex>
#include <pcrecpp.h>
#include <string>

class SmartRouter : public Php::Base {
    /**
     * @brief for private method under SmartRouter class, used for utils/helper each worker method for each purpose
     * 
     */

    private: void static replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    /**
     * @brief return split uri_route to array of uri with delim "/" and return size/length of splitted uri_route
     */

    public: Php::Value static uri_route_split(std::string uri_route, bool state = false) {
        
        /**
         * use conditionals for only slash routing
         * if uri_route only a "/" capture and use second conditional
         * if state is given false return 0;
         * if state is give true return a piece of array given only "/" as elements.
         */
        
        if(uri_route == "/") {
            if(state) 
                return 0;
            else
                return {"/"};
        }

        /**
         * remove first slash and last slash in routing uri
         * e.g. /user/:id/../../ = user/:id/../..
         */

        uri_route.substr(1, uri_route.length() - 2);
        
        /**
         * split uri_route as splitted by delim "/"
         * e.g. /user/:id/.. = ["user", ":id"]
         */

        std::vector<std::string> uri_route_split = utils::str_split("/", uri_route);

        /**
         * return context from what second argumen
         * when second argumen is:
         * false : return uri_route as array of splitted by delim "/"
         * true  : return uri_route length/size
         */

        if(state) 
            return (int)uri_route_split.size();
        else
            return uri_route_split;
    }

    /**
     * @brief push each uri based from length for uri_route routing, using splitted uri_route_split.
     *        e.g. /home/:get/:id/edit  = [/home/:get/:id/edit]  => 4
     *             /user/:id/:action/do = [/user/:id/:action/do] => 4
     */

    public: void static catch_uri_parse(std::string uri_route) {
        Php::Value FS_Uri_RCC = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count"});
        FS_Uri_RCC[uri_route] = uri_route_split(uri_route, true);   
        Database::set::array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count"}, FS_Uri_RCC);   
    }

    /**
     * @brief grouping splitted route from $_SESSION[...FS_Uri_Route_Char_Count] to each length
     *        e.g. /home/:get/:id/edit  = [/home/:get/:id/edit]  => 4
     *             /user/:id/:action/do = [/user/:id/:action/do] => 4
     *        ===> [4] => [
     *                      "/home/:get/:id/edit" ,
     *                      "/user/:id/:action/do",
     *                    ]
     * 
     */

    public: void static parsing_uri() {
        Php::Value FS_Uri_Route_Char_Count = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count"});
        
        for(auto &parent : FS_Uri_Route_Char_Count) {
            Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count_Parsed", parent.second});
            for(auto &child : FS_Uri_Route_Char_Count) {
                if(parent.second == child.second)
                    if(!Php::call("in_array", child.first, Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count_Parsed", parent.second})))
                        Database::set::push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count_Parsed", parent.second}, child.first);
            }
        }
    }

    public: void static v_double(std::string uri_route) {
        Php::Value web_route_list = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"});
        if(Php::call("in_array", uri_route, web_route_list).boolValue()) {
            Error::message::v_double_uri();
        }
    }

    public: void static match_uri_identitcs(std::string uri_x, std::string uri_y) {
        Php::Value uri_x_parsed = uri_route_split(uri_x, false);
        Php::Value uri_y_parsed = uri_route_split(uri_y, false);
        
        int route_length = Php::count(uri_x_parsed);
        int route_identic_passed = 0;

        for(auto &f_uri_x : uri_x_parsed) {
            std::string ftr_uri_x = f_uri_x.second;
            std::string ftr_uri_y = uri_y_parsed[f_uri_x.first];

            replaceAll(ftr_uri_x, "$fs_bs$", "\\");
            replaceAll(ftr_uri_y, "$fs_bs$", "\\");

            const char *str_uri_x = ftr_uri_x.c_str();
            const char *str_uri_y = ftr_uri_y.c_str();

            for(auto &exp : std::vector<const char *> {
                "^(?!:)[\\w+\\-\\:\\.\\_\\~\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\:\\@]*$",
                "^\\:[\\w+_-]*$",
                "^\\:\\w+\\:\\:\\(.*?\\)$"}) {
                regexp::match(exp, str_uri_x, [&](const char * matched) {
                    regexp::match("^(?!:)[\\w+\\-\\:\\.\\_\\~\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\:\\@]*$", str_uri_y, [&](const char * x) {
                        if((std::string)str_uri_x == (std::string)str_uri_y) { 
                            route_identic_passed++;
                        }

                        if((std::string)exp == std::string("^\\:[\\w+_-]*$")) {
                            route_identic_passed++;
                        }
                        
                            if((std::string)exp == std::string("^\\:\\w+\\:\\:\\(.*?\\)$"))
                            route_identic_passed++;
                    });

                    regexp::match("^\\:[\\w+_-]*$", str_uri_y, [&](const char * y) {
                        if((std::string)exp == std::string("^(?!:)[\\w+\\-\\:\\.\\_\\~\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\:\\@]*$"))
                            route_identic_passed++;

                        if((std::string)exp == std::string("^\\:[\\w+_-]*$"))
                            route_identic_passed++;

                        if((std::string)exp == std::string("^\\/\\:\\w+\\:\\:\\(.*?\\)$"))
                            route_identic_passed++;
                    });

                    regexp::match("^\\:\\w+\\:\\:\\(.*?\\)$", str_uri_y, [&](const char *oe) {
                        if((std::string)exp == std::string("^(?!:)[\\w+\\-\\:\\.\\_\\~\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\:\\@]*$"))
                            route_identic_passed++;

                        if((std::string)exp == std::string("^\\:[\\w+_-]*$"))
                            route_identic_passed++;
                        
                        if((std::string)exp == std::string("^\\/\\:\\w+\\:\\:\\(.*?\\)$"))
                            route_identic_passed++;
                    });
                });
            }
        }
        
        if(route_identic_passed >= route_length)
            Error::message::match_uri_identics();
    }

    public: void static validate_uri_identics() {
        Php::Value FS_Uri_RI = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count_Parsed"});

        for(auto &uri : FS_Uri_RI) {
            if(Php::count(uri.second) > 1) 
                for(auto &uri_parsed : uri.second) {
                    for(auto &uri_parsed_pattern : uri.second) {
                        if(uri_parsed.first != uri_parsed_pattern.first) 
                            match_uri_identitcs(uri_parsed.second, uri_parsed_pattern.second);
                    }
                }
        }
    }

    public: void static smart_uri_validator() {
        parsing_uri();
        
        validate_uri_identics();
    }

};