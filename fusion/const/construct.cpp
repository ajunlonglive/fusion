#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/error/message.cpp>

#include <iostream>

namespace Construct {
    void framework() {
        std::string FS_FRAMEWORK_MODE = Database::get::string({"FUSION_STORE", "FS_FRAMEWORK_MODE"});   
        if(!Database::isset::string(FS_FRAMEWORK_MODE)) {
            Error::message::empty_framework_mode();
        }
    }

    void framework_init(Php::Parameters &param) {
        if(Php::count(param) < 1) {
            Error::message::empty_framework_mode();
        }
        
        Php::Value FUSION_DB;
        FUSION_DB["FS_FRAMEWORK_MODE"] = param[0];

        Database::set::array({"FUSION_STORE"}, FUSION_DB);

        Database::set::empty_array({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"});
    }
    
    void route_init() {
        std::string Request_Uri = Php::eval("return $_SERVER['REQUEST_URI'];").stringValue();       
        
        Database::set::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"}, Request_Uri); 
        Database::set::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"}, true);
        
    }
}