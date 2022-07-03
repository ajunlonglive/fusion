#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/http/request/input-capture.h>

class Request : public Php::Base {
    public: std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
    public: std::string uri_route;
    
    public: Php::Value input(Php::Parameters &value) {
        if(Php::count(value) < 1) {
            Php::error << "Empty Argumen input<br />" << std::flush;
        }

        SmartRouter::replaceAll(uri_route, "$fs_bs$", "\\");

        std::string uri_subject = (Php::Value) value[0];

        InputCapture::is_capturable(uri_subject, uri_route);
        // Php::Value InputCapture::parse_input_capturable(uri_subject, uri_route);
        return (InputCapture::parse_input_capturable(uri_subject, uri_route))[uri_subject];
    }   
};