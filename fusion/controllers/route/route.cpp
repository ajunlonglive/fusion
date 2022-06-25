#pragma once

#include <phpcpp.h>

#include <fusion/const/construct.cpp>
#include <fusion/controllers/route/service.cpp>

#include <iostream>

class Route : public Php::Base {
    public: Route() {
        Construct::framework();
    }

    public: void static Get(Php::Parameters &param) {
        Route __construct;

        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        std::string uri_route   = param[0];
        Php::Value handler_opt  = param[1];

        RouteService::web::patch(uri_route);
        
        if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
            RouteService::web::assign(uri_route, handler_opt);
        }
    }
};