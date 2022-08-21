#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <components/gate/route/provider/service.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <database/core.hpp>
#include <regex/route.hpp>
#include <iostream>

class RouteGet : public Php::Base {

    // constructor
    public: RouteGet(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

        if(request_method == "GET") {
            Php::Value uri_route   = param[0];
            Php::Value handler_opt  = param[1];

            if(Php::is_array(uri_route).boolValue()) {
                // multi uri request e.g. Route::get(["/foo", "/bar"], function() {});
                for(auto &uri_each : uri_route) {
                    assign_to_route_service((std::string)uri_each.second, handler_opt);
                }
            } else {
                // single uri request e.g. Route::get("/foo", function() {});
                assign_to_route_service(uri_route, handler_opt);
            }
        }
    }   

    public: void assign_to_route_service(std::string uri_route, Php::Value handler_opt) {
        Php::Value parsed_uri_route_list;

        std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");

        std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
        
        bool permist_step = Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "Permist_Step"});

        RouteService::web::push(escape_uri_route);
        if(SmartRouter::regist(escape_uri_route, permist_step)) {
            parsed_uri_route_list = Database::get::array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Lists"});
        }

        // The gate for check if current $_SERVER["REQUEST_URI"] request same as user route address
        if(permist_step && SmartRouter::validate(parsed_uri_route_list[escape_uri_route], escape_uri_route, request_uri)) {
            
            // Change GET_METHOD parameter to "true" for tell to Router Service, if routing request method given
            Database::set::string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"}, "false");

            // Assign request context to Router Services
            RouteService::web::assign(escape_uri_route, handler_opt, "GET");
        }
    }
};