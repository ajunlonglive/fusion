#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/http/request/input-capture.h>

class Request : public Php::Base {
    public: std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
    public: Php::Value input_capture;
    
    public: void input(Php::Parameters &value) {
        Php::Value uri = value[0];

        InputCapture::is_capturable((std::string)uri, request_uri);
        InputCapture::parse_input_capturable((std::string)uri);
    }   
};