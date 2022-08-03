#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <components/gate/route/provider/service.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <database/core.hpp>
#include <regex/route.hpp>
#include <iostream>

#include <algorithm>
#include <string>
#include <vector>
#include <functional>

int testf() {
    return 0;
}

class RouteMethod : public Php::Base {

    // constructor
    public: RouteMethod(Php::Parameters &param) {
        if(Php::count(param) < 3) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 3)
            Error::message::many_route_get_param();

        std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

        std::map<std::string, std::function<int()>> method_list_hitted;
        method_list_hitted["GET"] = std::bind(&RouteMethod::get_method, this);
        method_list_hitted["POST"] = std::bind(&RouteMethod::post_method, this);;
        method_list_hitted["PUT"] = std::bind(&RouteMethod::put_method, this);;
        method_list_hitted["PATCH"] = std::bind(&RouteMethod::patch_method, this);;
        method_list_hitted["DELETE"] = std::bind(&RouteMethod::delete_method, this);;
        method_list_hitted["OPTIONS"] = std::bind(&RouteMethod::options_method, this);;

        bool is_method_valid = false;
        for(auto &each_method : (Php::Value)param[0]) {
            std::string method_temp = (const char *) each_method.second;
            std::transform(method_temp.begin(), method_temp.end(),method_temp.begin(), ::toupper);

            if(request_method == method_temp) {
                method_list_hitted[request_method]();
                is_method_valid = true;
                break;
            }
        }

        if(is_method_valid) {
            std::string uri_route   = param[1];
            Php::Value handler_opt  = param[2];

            std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");

            RouteService::web::push(escape_uri_route);
            SmartRouter::catch_uri_parse(escape_uri_route);

            if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
                std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

                if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_route == request_uri) {
                    // Change PUT_METHOD parameter to "true" for tell to Router Service, if routing request method given
                    // Database::set::string({"FUSION_STORE", "FS_ROUTE", "OPTIONS_METHOD", "is_null"}, "false");

                    // Assign request context to Router Services
                    RouteService::web::assign(escape_uri_route, handler_opt, "METHOD");
                }
            }
        }
    }

    public: int get_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"}, "false"); return 0; }
    public: int post_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "POST_METHOD", "is_null"}, "false"); return 0; }
    public: int put_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"}, "false"); return 0; }
    public: int patch_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "PATCH_METHOD", "is_null"}, "false"); return 0; }
    public: int delete_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "DELETE_METHOD", "is_null"}, "false"); return 0; }
    public: int options_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "OPTIONS_METHOD", "is_null"}, "false"); return 0; }
    public: int head_method() { Database::set::string({"FUSION_STORE", "FS_ROUTE", "HEAD_METHOD", "is_null"}, "false"); return 0; }
};