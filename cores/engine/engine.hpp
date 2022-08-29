#pragma once

#include <phpcpp.h>
// #include <transport/session.hpp>
#include <cores/autoload/autoload.hpp>
#include <error/message.hpp>
#include <constructor/constructor.hpp>
#include <destructor/destructor.hpp>

#include <iostream>
#include <sstream>

namespace cores {


class c_engine : public Php::Base {
    public: c_engine() {
        constructor::c_run::m_framework();
    }   

    public: virtual ~c_engine() {}

    public: void static m_framework(Php::Parameters &param) {
        // Start local database for bridge communication
        constructor::c_run::m_start_session_db();

        // Start to initiliazed all variabled used for framework proccess
        constructor::c_run::m_framework_init(param);

        // Start to initialized 
        constructor::c_run::m_route_init();

    }

    public: void static m_config(Php::Parameters &param) {
        // Start to handle Internal Php Error with FusionErrorHandler
        constructor::c_run::m_internal_error_handler();
    }

    public: void static m_run() {
        c_engine __construct;
        
        // // Start to handle Internal Php Error with FusionErrorHandler
        // destructor::c_run::m_internal_error_handler();

        destructor::c_run::m_route_init();

        destructor::c_run::m_session_reset();
    }

};


}