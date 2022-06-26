#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/http/request/input-capture.h>

class Request : public Php::Base {
    public: std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
    public: Php::Value input_capture;
    public: void input() {
        InputCapture::is_capturable(request_uri);

    }   
};