#pragma once

#include <phpcpp.h>

#include <fusion/const/construct.cpp>
#include <fusion/components/gate/route/provider/service.h>
#include <fusion/regex/route.h>
#include <iostream>

class RouteGet : public Php::Base {
    public: RouteGet(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        std::string uri_route   = param[0];
        std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");
        Php::Value handler_opt  = param[1];

        RouteService::web::patch(escape_uri_route);
        SmartRouter::catch_uri_parse(escape_uri_route);

        if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
            RouteService::web::assign(escape_uri_route, handler_opt);
        }

    }

    public: void test() {
        Php::out << "<br />hello test" << "<br />" << std::flush;
    }

    public: ~RouteGet() {}
};