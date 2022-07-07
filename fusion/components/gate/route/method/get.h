#pragma once

#include <phpcpp.h>

#include <fusion/const/construct.cpp>
#include <fusion/components/gate/route/provider/service.h>
#include <fusion/components/gate/route/provider/smart.h>
#include <fusion/regex/route.h>
#include <iostream>

class RouteGet : public Php::Base {

    // constructor
    public: RouteGet(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        if(Php::eval("return $_SERVER['REQUEST_METHOD'];").stringValue() == "GET") {
            std::string uri_route   = param[0];
            std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");
            Php::Value handler_opt  = param[1];

            RouteService::web::push(escape_uri_route);
            SmartRouter::catch_uri_parse(escape_uri_route);

            if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
                std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

                // The gate for check if current $_SERVER["REQUEST_URI"] request same as user route address
                if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_route == request_uri) {

                    // Php::Value gett = param;
                    // std::string cclass = gett[1][0];
                    // std::string mmethod = gett[1][1];

                    // Container::loader(cclass, mmethod);

                    RouteService::web::assign(escape_uri_route, handler_opt);
                }
            }
        }

    }   

    public: void test() {
        Php::out << "<br />hello test" << "<br />" << std::flush;
    }

    public: ~RouteGet() {}
};