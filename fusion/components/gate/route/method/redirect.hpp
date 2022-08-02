#pragma once

#include <phpcpp.h>

#include <fusion/constructor/constructor.hpp>
#include <fusion/components/gate/route/provider/service.hpp>
#include <fusion/components/gate/route/provider/smart.hpp>
#include <fusion/database/core.hpp>
#include <fusion/regex/route.hpp>
#include <iostream>

class RouteRedirect : public Php::Base {

    // constructor
    public: RouteRedirect(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        std::string uri_type = Php::call("gettype", (Php::Value)param[1]).stringValue();
        if(uri_type != "string")
            Error::message::untype_route_redirect_param(uri_type);

        std::string request_method = Database::get::string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

            std::string uri_route   = param[0];
            std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");
            Php::Value handler_opt  = param[1];

            RouteService::web::push(escape_uri_route);
            SmartRouter::catch_uri_parse(escape_uri_route);

            if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
                std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

                if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_route == request_uri) {
                    Database::set::string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"}, "false");

                    RouteService::web::assign(escape_uri_route, handler_opt, "REDIRECT");
                }
            }
    }

};