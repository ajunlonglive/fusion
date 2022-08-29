#pragma once

#include <phpcpp.h>

#include <error/message.hpp>
#include <cores/autoload/loader.hpp>
#include <constructor/constructor.hpp>

namespace cores {


    class c_autoload : public Php::Base {
        public: void static m_config(Php::Parameters &param) {
            constructor::c_run::m_framework();

            if(Php::count(param) < 1)
                Error::message::empty_autoload_config_param();
            if(Php::count(param) > 1)
                Error::message::many_autoload_config_param();

            
            std::string autoload_config_mode = param[0];
            if(autoload_config_mode == "FS_DEFAULT") {
                cores::autoload::c_loader::m_default();          
                return void();
            }

            if(autoload_config_mode == "FS_COMPACT") {
                Php::out << "autoload_compact" << std::flush;
                return void();
            }

            return void();
        }  

        public: void static m_register_config() {
            // Register the config as startup used for require_src
            cores::autoload::c_loader::m_framework_config();
            return void();
        }

        public: void static m_register_app() {
            // Register the config as startup used for require_src
            cores::autoload::c_loader::m_default_app();
            return void();
        }
    };

}