#pragma once

#include <phpcpp.h>

#include <transport/session/session.hpp>
#include <error/message.hpp>
#include <regex/route.hpp>
#include <services/route/guard.hpp>
#include <filesystem>

#include <iostream>

namespace Construct {
    void framework() {
        std::string FS_FRAMEWORK_MODE = transport::session::c_get::m_string({"FUSION_STORE", "FS_FRAMEWORK_MODE"});   
        if(!transport::session::c_isset::m_string(FS_FRAMEWORK_MODE)) {
            Error::message::empty_framework_mode();
        }
    }

    void framework_init(Php::Parameters &param) {
        if(Php::count(param) < 1) {
            Error::message::empty_framework_mode();
        }
        
        Php::Value FUSION_DB;
        FUSION_DB["FS_FRAMEWORK_MODE"] = param[0];

        transport::session::c_set::m_array({"FUSION_STORE"}, FUSION_DB);
    }

    void start_session_db() {
        Php::call("session_start");
    }

    void route_init() {
        std::string request_uri = Php::eval("return $_SERVER['REQUEST_URI'];").stringValue();       

        std::string escape_request_uri = Regex::uri::escape_request_uri(request_uri);

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
}