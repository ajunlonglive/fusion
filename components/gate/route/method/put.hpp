#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <services/route/route.hpp>
#include <services/route/guard.hpp>
#include <transport/session/session.hpp>
#include <error/routemethod.hpp>
#include <regex/route.hpp>

#include <iostream>


namespace components {
    namespace gate {
        namespace route {
            namespace method {


class c_route_put : public Php::Base {

    // Constructor init for singleton Route Accessor
    public: c_route_put(Php::Parameters &param) {
        // Init param length from parameter
        int param_count = Php::count(param);

        /**
         * @brief Param length must be "2" if less or more than 2, it will throw exception
         */

        // If param length less than 2 return exception empty_route_get_param()
        if(param_count < 2) 
            Error::message::empty_route_get_param();

        // If param length more than 2 return exception many_route_get_param()
        if(param_count > 2)
            Error::message::many_route_get_param();

        // When arguments prop is not same for conditional, throw errors  
        error::route::method_prop_args(param);   

        // Get current route_hitted for guard checking if routing already response
        std::string route_hitted = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"});
        
        // If routing already response, break the execution
        if(route_hitted != "" ) return;

        // Get request_method when user access the uri
        // !REQUEST_METHOD initialized coming from internal constructor Fusion
        std::string request_method = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});

        // If request_method was "PUT"
        if(request_method == "PUT") {
            // Raw uri_route
            Php::Value uri_route = param[0];

            // Option for callback or action
            Php::Value handler_opt = param[1];

            if(Php::is_array(uri_route).boolValue()) {
                // Multi uri request e.g. Route::put(["/foo", "/bar"], function() {});
                for(auto &uri_each : uri_route) {
                    assign_to_route_service((std::string)uri_each.second, handler_opt);
                }
            } else {
                // Single uri request e.g. Route::put("/foo", function() {});
                assign_to_route_service(uri_route, handler_opt);
            }
        }
    }   

    public: void assign_to_route_service(std::string uri_route, Php::Value handler_opt) {
        Php::Value parsed_uri_route_list;

        // Escaping uri_route for doubling slash convert to single slash
        std::string escape_uri_route = regex::c_uri::m_escape_request_uri(uri_route + "/");

        // Get FS_REQUEST_URI from user client request
        // !FS_REQUEST_URI initialized coming from internal constructor Fusion
        std::string request_uri = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
        
        // Get permist_step in false value for blocking services::route::c_guard::m_validate
        bool permist_step = transport::session::c_get::m_boolean({"FUSION_STORE", "FS_ROUTE", "Permist_Step"});

        // Push the escaped uri route to FS_Web_Route_Lists
        services::route::c_web::m_push(escape_uri_route);

        // When permist_step still false (a first step SmartRouter running), regist escaped uri_route to FS_Web_Route_Identics_Lists
        if(services::route::c_guard::m_regist(escape_uri_route, permist_step)) {
            parsed_uri_route_list = transport::session::c_get::m_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Lists"});
        }

        // permist_step used for blocking services::route::c_guard::m_validate
        // When secondstep SmartRouter running, permist step setted to true which is make services::route::c_guard::m_validate can run
        if(permist_step && services::route::c_guard::m_validate(parsed_uri_route_list[escape_uri_route], escape_uri_route, request_uri)) {
            
            // Set GET_METHOD "is_null" to false
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"}, "false");

            // Finally, assign uri_route, ptional handle, request method to RouteService
            services::route::c_web::m_assign(escape_uri_route, handler_opt, "PUT");
        }
    }
};


            }
        }
    }
}