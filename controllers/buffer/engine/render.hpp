#pragma once

#include <phpcpp.h>

#include <database/core.hpp>

#include <iostream>

class output_render : public Php::Base {

    public: void static start(Php::Parameters &param) {
        Database::set::string({"FUSION_STORE", "FS_BUFFER_CONTEXT", "FS_MAIN_RENDER"}, "test");
        // Php::call("ob_start");
    }

    public: void static end(Php::Parameters &param) {
        std::string buffer = Database::get::string({"FUSION_STORE", "FS_BUFFER_CONTEXT", "FS_MAIN_RENDER"});
        Php::out << buffer << std::flush;    
    }

};