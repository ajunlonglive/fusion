#pragma once

#include <phpcpp.h>

#include <cores/container/container.hpp>
#include <transport/session/session.hpp>
#include <error/message.hpp>
#include <http/request/request.hpp>
#include <regex/route.hpp>
#include <services/route/guard.hpp>
#include <cores/container/container.hpp>
#include <views/error/page.hpp>


#include <iostream>

#define COMPARE_REQ_METHOD(set, req, method) set ? true : req == method ? true : false;

namespace services {
    namespace route {

class c_web : public Php::Base {
    
    /**
     * @brief       Used for push each routing uri to SESSION "FS_Web_Route_List".
     * @note        SmartRouter::v_double which is will handle for double/twice routing from user script.
     * 
     * @param       uri_route (string) User router address
     * @return      void
     * 
     * @warning     SmartRouter::v_double() => (will throw (PHP) error if conditional meet it)
     */
    public: void static m_push(std::string uri_route) {
        // Default guard for checking double uri_route if more then one
        // SmartRouter::v_double(uri_route);
        // Push uri_route string to SESSION storage
        transport::session::c_set::m_push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Lists"}, uri_route);
    }

    /**
     * @brief Main method for assign routing to class controller, function callback and the return action
     * @note list of method assign:
     *       1. DI/Dependency Injection to controller class, with return action argument (see sub comment top of method)
     *       2. function callback with injected context/request from Http stuff (see sub comment top of method)
     * 
     * @param uri_route         (std::string) User router address
     * @param handler_opt       (Php::Value) A param for callback or action context
     * @param request_method    (std::string) Request method for parameter action (GET, POST, PUT, etc.)
     * 
     * @return void()       A void return only for blocking return each state conditional (blocking return)
     * 
     */
    public: void static m_assign(std::string uri_route, Php::Value handler_opt, std::string request_method) {

        /**
         * @note Reserved method for Redirect
         * 
         */
        
        transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"}, uri_route);

        /**
         * @note Reserved method for Get, Post, Put, Patch, Delete
         * 
         */
        bool set_method = request_method == "REDIRECT" ? true : false;
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "GET");
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "POST");
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "PUT");
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "PATCH");
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "DELETE");
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "ANY");
             set_method = COMPARE_REQ_METHOD(set_method, request_method, "METHOD");

        if(set_method) {

            // Redirect action, no need any inheritance
            if(request_method == "REDIRECT") {
                // Call header function, do Location command for redirect to destination
                Php::eval("header('Location: " +(std::string)handler_opt+ "');");

                // Break the script execution
                return void();
            }

            // Custom action controller, connected to DI Container
            if(Php::is_array(handler_opt).boolValue()) {      
                // Init and cast user_controller_name to string class name
                std::string user_controller_name = handler_opt[0];
                // Init and cast user_method_name to string method name
                std::string user_method_name     = handler_opt[1];

                if(Php::count(handler_opt) < 1)
                    Error::message::handler_opt_empty_args();

                if(Php::count(handler_opt) > 2)
                    Error::message::handler_opt_many_args();


                // Import default dependencies lib for Dependency Injection
                std::vector<Php::Value> args = cores::c_container::m_method(user_controller_name, user_method_name);

                // Declare class method for init object class
                Php::Value class_method;
                // Set class name first with initialized
                class_method[0] = Php::Object(user_controller_name.c_str());
                // Then set method name
                class_method[1] = user_method_name;
                
                // Call the method with injected dependencies
                Php::call("call_user_func_array", class_method, args);

                // Break the script execution
                return void();
            }               

            // Single action controller, connected to DI Container
            if(!Php::call("is_object", handler_opt).boolValue() && Php::call("class_exists", handler_opt).boolValue()) {
                // Init and cast handler_opt to string class name
                std::string user_controller_name = handler_opt;

                // Import default dependencies lib for Dependency Injection
                std::vector<Php::Value> args = cores::c_container::m_method(user_controller_name, "__invoke");

                // Setup for DI to PHP __construct()
                // Php::Value reflect_class = Php::Object("ReflectionClass", user_controller_name);
                // Php::Value class_init = reflect_class.call("newInstanceArgs", args);

                // Declare class method for init object class
                Php::Value class_method;
                // Set class name first with initialized
                class_method[0] = Php::Object(user_controller_name.c_str());
                // Then set method name
                class_method[1] = "__invoke";
                
                // Call the method with injected dependencies
                Php::call("call_user_func_array", class_method, args);

                // Break the script execution
                return void();
            }

            // Closure callback controller, connected to DI Container
            if(Php::call("is_callable", handler_opt).boolValue()) {
                // Import default dependencies lib for Dependency Injection
                std::vector<Php::Value> args = cores::c_container::m_function(handler_opt);

                // call the callback with injected dependencies
                Php::call("call_user_func_array", handler_opt, args);

                return void();
            }

            // Throw error exception for not given conditional arguments
            // ...
        }
    }

    /**
     * @brief flush all session in RouteService such session storage, error handler, and etc.
     * 
     */
    public: void static m_flush() {
        // flush session storage


        // handle error page/header for incoming http request
        std::string request_method = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"});


        std::string get_method  = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"});
        std::string post_method = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "POST_METHOD", "is_null"});
        std::string put_method = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"});
        std::string patch_method = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "PATCH_METHOD", "is_null"});
        std::string delete_method = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "DELETE_METHOD", "is_null"});

        if(get_method    == "true" && request_method == "GET")         error_page::Get::code_404();    
        if(post_method   == "true" && request_method == "POST")        error_page::Post::code_404();   
        if(post_method   == "true" && request_method == "HEAD")        error_page::Post::code_404();   
        if(put_method    == "true" && request_method == "PUT")         error_page::Put::code_404();   
        if(patch_method  == "true" && request_method == "PATCH")       error_page::Patch::code_404();   
        if(delete_method == "true" && request_method == "DELETE")      error_page::Delete::code_404();    
        if(delete_method == "true" && request_method == "OPTIONS")     error_page::Delete::code_404();    

    }

    /**
     * @brief Reset the SESSION "FS_Web_Route_List" to the empty array
     * 
     * @return void()
     */
    public: void static m_reset_route_list() {
        transport::session::c_set::m_empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Lists"});
    }

};


    }
}
