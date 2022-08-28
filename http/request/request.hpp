#pragma once

#include <phpcpp.h>
#include <transport/session/session.hpp>
#include <http/request/utils.hpp>
#include <error/message.hpp>
#include <utils/string.hpp>


namespace http {


class c_request : public Php::Base {
    public: std::string request_uri = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
    public: std::string uri_route = transport::session::c_get::m_string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"});
    public: bool url_accessor = false;
    
    public: c_request() = default;

    public: void __construct() {
        Php::Value self(this);
        // self["get"] = "";
        // method();
    }
    
    public: Php::Value m_url() {
        url_accessor = true;
        return (Php::Object)this;
    }

    public: Php::Value m_path() {
        if(!url_accessor) Error::message::request_url_need_accessor("path");
        url_accessor = false;
        return request_uri;
    }

    public: Php::Value m_full() {
        if(!url_accessor) Error::message::request_url_need_accessor("full");
        url_accessor = false;
        return "http://localhost" + request_uri;
    }
};


}