#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/cores/autoload/autoload.cpp>
#include <fusion/error/message.cpp>
#include <fusion/const/construct.cpp>
#include <fusion/dest/destruct.cpp>

#include <iostream>
#include <sstream>

class Engine : public Php::Base {
    public: Engine() {
        Construct::framework();
    } 

    public: virtual ~Engine() {}

    public: void static Framework(Php::Parameters &param) {
        Construct::framework_init(param);
        Construct::route_init();
    }

    public: void static Run() {
        Engine __construct;
        
        Destruct::route_init();
    }

};