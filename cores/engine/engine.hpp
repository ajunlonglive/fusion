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
        Construct::framework();
    }   

    public: virtual ~c_engine() {}

    public: void static m_framework(Php::Parameters &param) {
        // Start local database for bridge communication
        Construct::start_session_db();

        // Start to initiliazed all variabled used for framework proccess
        Construct::framework_init(param);

        // Start to initialized 
        Construct::route_init();
    }

    public: void static m_run() {
        c_engine __construct;
        
        // Start to handle Internal Php Error with FusionErrorHandler
        Destruct::internal_error_handler();

        Destruct::route_init();

        Destruct::session_reset();
    }

};


}