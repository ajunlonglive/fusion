#pragma once

#include <phpcpp.h>

#include <fusion/database/core.cpp>
#include <fusion/error/message.cpp>
#include <fusion/http/request/request.cpp>
#include <fusion/regex/route.h>
#include <fusion/http/request/input-capture.h>
#include <fusion/components/gate/route/provider/smart.h>

#include <iostream>

namespace RouteService {
    class web : public Php::Base {
        
        /**
         * @brief used for push a each routing uri to $_SESSION[FS_Web_Route_List]
         *        - completely with SmartRouter::v_double which is will handle for double/twice routing
         *        - from user script. (will throw error if conditional meet it)
         */

        public: void static patch(std::string uri_route) {
            SmartRouter::v_double(uri_route);
            // std::string escape_uri = std::regex_replace(uri_route, std::regex("\\$\\fs\\_bs\\$"), "\\");
            Database::set::push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"}, uri_route);
        }

        /**
         * @brief main method for assign routing to class controller, function callback and the return action
         *        list of method assign:
         *        1. DI/Dependency Injection to controller class, with return action argument
         *        2. function callback with injected context/request from Http stuff
         */

        public: Php::Value static assign(std::string uri_route, Php::Value handler_opt) {
            std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

            
            if(!SmartRouter::handle_input_uri_guard(uri_route)) {
                if(uri_route != request_uri) {
                    Php::out << "IM HERE" << "<br />" << std::flush;
                    return 0;         
                }
            }
                
            // the gate for check if current $_SERVER["REQUEST_URI"] request same as routing address
            

            // 1. Router handler with Dependencies Injection
            if(Php::is_array(handler_opt).boolValue()) {            
                if(Php::count(handler_opt) < 2)
                    Error::message::handler_opt_empty_args();

                if(Php::count(handler_opt) > 2)
                    Error::message::handler_opt_many_args();

                std::string user_controller_name = handler_opt[0];
                const char* user_method_name     = handler_opt[1];

                Request *request = new Request();
                request->uri_route = uri_route;        

                Php::Object user_controller;

                if(Php::call("method_exists", user_controller_name, "__construct").boolValue()) {
                    user_controller = Php::Object(user_controller_name.c_str(),  Php::Object("Fusion\\Http\\Request", request));
                    user_controller.call(user_method_name);
                } else {
                    user_controller = Php::Object(user_controller_name.c_str());
                    user_controller.call(user_method_name, Php::Object("Fusion\\Http\\Request", request));
                }

                return 0;
            }               

            // 2. Router handler with callback action, injected Request as param

            if(Php::call("is_callable", handler_opt).boolValue()) {
                Request *request = new Request;
                request->uri_route = uri_route;        

                handler_opt(Php::Object("Fusion\\Http\\Request", request));
                return 0;
            }

            return 0;
        }

        /**
         * @brief reset the $_SESSION[FS_Web_Route_List] to the empty array
         */

        public: void static reset_route_list() {
            Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"});
        }

    };
}