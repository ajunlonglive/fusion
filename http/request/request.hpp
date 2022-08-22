#pragma once

#include <phpcpp.h>
#include <database/core.hpp>
#include <http/request/input-capture.hpp>
#include <http/request/utils.hpp>
#include <error/message.hpp>
#include <utils/string.hpp>

class Request : public Php::Base {
    public: std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
    public: std::string uri_route = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"});
    public: bool url_accessor = false;
    
    public: Request() = default;

    public: void __construct() {
        Php::Value self(this);
        // self["get"] = "";
        // method();
    }
    
    public: Php::Value url() {
        url_accessor = true;
        return (Php::Object)this;
    }

    public: Php::Value path() {
        if(!url_accessor) Error::message::request_url_need_accessor("path");
        url_accessor = false;
        return request_uri;
    }

    public: Php::Value full() {
        if(!url_accessor) Error::message::request_url_need_accessor("full");
        url_accessor = false;
        return "http://localhost" + request_uri;
    }
};