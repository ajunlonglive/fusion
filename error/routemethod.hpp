#pragma once

#include <phpcpp.h>

#include <error/message.hpp>

#define COMPARE_REQ_PROP(set, req) set ? true : req ? true : false;


namespace error {
    class route {
        public: void static method_prop_args(Php::Parameters &param) {
            // Set attribute used for conditional args prop
            bool arg_uri_route = Php::call("is_string", param[0]);

            bool arg_handler_route = false;
            arg_handler_route = COMPARE_REQ_PROP(arg_handler_route, Php::call("is_callable", param[1]));
            arg_handler_route = COMPARE_REQ_PROP(arg_handler_route, Php::call("is_array", param[1]));  

            Php::Value class_name = param[1];
            if(!Php::call("is_array", class_name) && !Php::call("is_object", class_name)) {
                arg_handler_route = COMPARE_REQ_PROP(arg_handler_route, Php::call("class_exists", class_name));
            } else {
                arg_handler_route = COMPARE_REQ_PROP(arg_handler_route, Php::call("is_string", class_name));
            }
            
            // Use attribute in conditional
            if(!arg_uri_route || !arg_handler_route)  
                // When user do a human error, throw error
                Error::message::arg_prop_error();
        }

         public: void static method_prop_args_redirect(Php::Parameters &param) {
                // Set attribute used for conditional args prop
            bool arg_uri_route = Php::call("is_string", param[0]);

            bool arg_handler_route = false;
            arg_handler_route = COMPARE_REQ_PROP(arg_handler_route, Php::call("is_string", param[1]));

            // Use attribute in conditional
            if(!arg_uri_route || !arg_handler_route) 
                // When user do a human error, throw error
                Error::message::arg_prop_error();
        }
    };
}