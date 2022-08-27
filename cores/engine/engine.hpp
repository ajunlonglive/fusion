#pragma once

#include <phpcpp.h>
#include <database/core.hpp>
#include <cores/autoload/autoload.hpp>
#include <error/message.hpp>
#include <constructor/constructor.hpp>
#include <destructor/destructor.hpp>

#include <iostream>
#include <sstream>

class Engine : public Php::Base {
    public: Engine() {
        Construct::framework();
    }   

    public: virtual ~Engine() {}

    public: void static Framework(Php::Parameters &param) {
        // Start local database for bridge communication
        Construct::start_session_db();

        // Start to initiliazed all variabled used for framework proccess
        Construct::framework_init(param);

        // Start to handle Internal Php Error with FusionErrorHandler
        // Construct::internal_error_handler();

        // Start to initialized 
        Construct::route_init();
    }

    public: void static Run() {
        Engine __construct;
        
        Destruct::internal_error_handler();

        Destruct::route_init();

        Destruct::session_reset();
    }

};