#pragma once

#include <phpcpp.h>

#include <transport/session/session.hpp>
#include <error/message.hpp>
#include <regex/route.hpp>
#include <services/route/guard.hpp>
#include <filesystem>
#include <regex/wrapper/pcre2.hpp>

#include <iostream>

namespace constructor {

    class c_run {

        public: void static m_framework() {
            std::string FS_FRAMEWORK_MODE = transport::session::c_get::m_string({"FUSION_STORE", "FS_FRAMEWORK_MODE"});   
            if(!transport::session::c_isset::m_string(FS_FRAMEWORK_MODE)) {
                Error::message::empty_framework_mode();
            }
        }

        public: void static m_framework_init(Php::Parameters &param) {
            if(Php::count(param) < 1) {
                Error::message::empty_framework_mode();
            }
            
            Php::Value FUSION_DB;
            FUSION_DB["FS_FRAMEWORK_MODE"] = param[0];

            transport::session::c_set::m_array({"FUSION_STORE"}, FUSION_DB);
        }

        public: void static m_start_session_db() {
            Php::call("session_start");
            
            // regexp::match("(?<first>hello)|(?<second>semua)", "hello semua", [&](const char *matched) {
            //     Php::out << matched << std::flush;
            // });
        }

        public: void static m_route_init() {
            std::string request_uri = Php::eval("return $_SERVER['REQUEST_URI'];").stringValue();       

            std::string escape_request_uri = regex::c_uri::m_escape_request_uri(request_uri);

            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"}, escape_request_uri); 
            // RedisDb::set::string("FUSION_STORE/FS_ROUTE/FS_REQUEST_URI", escape_request_uri);

            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "REQUEST_METHOD"}, Php::eval("return $_SERVER['REQUEST_METHOD'];").stringValue());

            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "GET_METHOD", "is_null"}, "true");
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "POST_METHOD", "is_null"}, "true");
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "HEAD_METHOD", "is_null"}, "true");
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "PUT_METHOD", "is_null"}, "true");
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "PATCH_METHOD", "is_null"}, "true");
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "DELETE_METHOD", "is_null"}, "true");
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "OPTIONS_METHOD", "is_null"}, "true");

            transport::session::c_set::m_string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"}, "");
            transport::session::c_set::m_empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Lists"});
            transport::session::c_set::m_empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Lists"});
            transport::session::c_set::m_empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Identics_Param"});
            transport::session::c_set::m_boolean({"FUSION_STORE", "FS_ROUTE", "Permist_Step"}, false);
            
            // RedisDb::set::push_array("FUSION_STORE/FS_ROUTE/FS_Web_Route_Identics_Param", {""});
            // RedisDb::set::push_array_field("FUSION_STORE/FS_ROUTE/FS_Web_Route_Identics_List", "null", "null");
            // RedisDb::set::string("FUSION_STORE/FS_ROUTE/Permist_Step", "false");

            // transport::session::c_set::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"}, true);

            // transport::session::c_set::m_empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Uri_Route_Char_Count"});    

            // Php::Value request_uri_split = SmartRouter::uri_route_split(escape_request_uri, false);
            // transport::session::c_set::m_push_array_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_Req_Uri_Split"}, request_uri_split);
        }

        public: void static m_internal_error_handler() {
            
            // When Serfix used for pre-parser to CGI, add data in dbcore to get actual script for error events
            std::string app_path = Php::call("dirname", Php::call("realpath", "index.php"), 2);
            transport::session::c_set::m_string({"FUSION_STORE", "FS_ERROR", "Filename"}, app_path);

            // Get data for error handler use to
            std::string php_error_handler = transport::session::c_get::m_string({"FUSION_STORE", "FS_ERROR", "Php_Error_Handler_Function"});

            // Set register shutdown for function PhpErrorHandler, to catch all error events
            Php::call("register_shutdown_function", php_error_handler);

        }

    };
    
}