#pragma once

#include <phpcpp.h>

#include <iostream>

class RouteContext : public Php::Base {
    public: std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});
    public: std::string uri_route = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_Route_Hitted"});
    public: bool uri_accessor = false;

    public: void code_501() {
        Php::out << "Error: 501" << std::flush;
    }

    public: Php::Value uri() {
        uri_accessor = true;
        return (Php::Object)this;
    }

    public: Php::Value parse(Php::Parameters &index_uri) {
        if(!uri_accessor) Error::message::request_url_need_accessor("parse");
        uri_accessor = false;
        // utils::replaceAll(uri_route, "$fs_bs$", "\\");

        std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"}); 

        std::vector<std::string> split_request_uri = RequestUtils::uri_route_split(request_uri, false);
        std::vector<std::string> split_uri_route = RequestUtils::uri_route_split(uri_route, false);

        Php::Value subject_uri = index_uri;
        Php::Value match_grouping_result;

        for(int i = 0; i < (int) split_uri_route.size(); i++) {
            regexp::match("(?<=^\\:)[\\w+_-]*$", split_uri_route[i].c_str(), [&](const char * matched) {
                if(Php::empty((Php::Value) index_uri) ||  Php::call("in_array", matched, subject_uri).boolValue())
                    match_grouping_result[matched] = split_request_uri[i];
            });

            regexp::match("(?<=^\\:\\:)[\\w+_-]*(?=\\(.*?\\)$)", split_uri_route[i].c_str(), [&](const char * uname) {
                regexp::match("(?<=\\().*?(?=\\))", split_uri_route[i].c_str(), [&](const char * matched2) {
                    regexp::match(matched2, split_request_uri[i].c_str(), [&](const char * matched3) {
                        if(Php::empty((Php::Value)index_uri) || Php::call("in_array", uname, subject_uri).boolValue())
                            match_grouping_result[uname] = matched3;
                    });
                });
            });
        }

        if(match_grouping_result) {
            if(match_grouping_result.size() == subject_uri.size() || subject_uri.size() < 1) {
                return match_grouping_result;
            }
            return Error::message::captureable_not_found();
        }

        return Error::message::captureable_not_found();
    }   
};