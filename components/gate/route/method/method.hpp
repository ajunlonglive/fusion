#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <services/route/route.hpp>
#include <services/route/guard.hpp>
#include <transport/session/session.hpp>
#include <error/routemethod.hpp>
#include <regex/route.hpp>

#include <iostream>

#include <algorithm>
#include <string>
#include <vector>
#include <functional>


namespace components {
    namespace gate {
        namespace route {
            namespace method {


class c_route_method : public Php::Base {
    // Constructor init for singleton Route Accessor
    public: c_route_method(Php::Parameters &param) {
        // Init param length from parameter
        int param_count = Php::count(param);

        /**
         * @brief Param length must be "3" if less or more than 2, it will throw exception
         */

        // If param length less than 3 return exception empty_route_get_param()
        if(param_count < 3) 
            Error::message::empty_route_get_param();

        // If param length more than 3 return exception many_route_get_param()
        if(param_count > 3)
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

        // Set variable for parameter grouping method compare to current request method
        bool is_method_valid = false;
        
        // Iterate grouping method (first param) for each method
        for(auto &each_method : (Php::Value)param[0]) {
            // Cast each method to string
            std::string str_method = (const char *) each_method.second;
            // Uppering all character from each method
            std::transform(str_method.begin(), str_method.end(), str_method.begin(), ::toupper);

            // Compare each method with current request method
            if(str_method == request_method) {
                // If compare was true, set is_method_valid to true
                is_method_valid = true;
                // Break the loop
                break;
            }
        }

        // If grouping method had request_method
        if(is_method_valid) {
            // Raw uri_route
            Php::Value uri_route = param[1];

            // Option for callback or action
            Php::Value handler_opt = param[2];

            if(Php::is_array(uri_route).boolValue()) {
                // Multi uri request e.g. Route::method(["get", "post"], ["/foo", "/bar"], function() {});
                for(auto &uri_each : uri_route) {
                    assign_to_route_service((std::string)uri_each.second, handler_opt, request_method);
                }
            } else {
                // Single uri request e.g. Route::method(["get", "post"], "/foo", function() {});
                assign_to_route_service(uri_route, handler_opt, request_method);
            }
        }
    }   

    public: void assign_to_route_service(std::string uri_route, Php::Value handler_opt, std::string request_method) {
        // Predefine parsed_uri_route_list to use after second step SmartRouter running
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
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", request_method+ "_METHOD", "is_null"}, "false");

            // Finally, assign uri_route, ptional handle, request method to RouteService
            services::route::c_web::m_assign(escape_uri_route, handler_opt, request_method);
        }
    }
};
        

            }
        }
    }
}