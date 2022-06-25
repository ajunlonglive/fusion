#pragma once

#include <phpcpp.h>

#include <iostream>


std::string cout(std::string messages) {
    return "<b>Fatal error:</b> FusionEngine: " +messages+ " {main:0} throw in <b id='fc'></b> on line <b id='lc'></b><br/><script>function z(x){return document.getElementById(x);}window.onload=function(){let b=z('el').innerHTML;let x=b.match(/(?<=\\<b\\>)\\/(.*?)(?=\\<\\/b\\>)|(?<=line <b>)(.*?)(?=\\<\\/b\\>)/g);z('fc').innerHTML=x[0];z('lc').innerHTML=x[1]; document.getElementById('el').style.display = 'none';}</script><div id='el'>";
}

namespace Error {
    class message {
        public: void static empty_framework_mode() {
            std::string error_message = cout("'Fusion/Cores/Engine::Framework()' not declared");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }
        
        public: void static empty_autoload_config_param() {
            std::string error_message = cout("'Fusion/Cores/Autoload::Config()' need more arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static many_autoload_config_param() {
            std::string error_message = cout("'Fusion/Cores/Autoload::Config()' too much arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static empty_route_get_param() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' need more arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }
        public: void static many_route_get_param() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' too much arguments");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static handler_opt_empty_args() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' second parameter need more context");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }

        public: void static handler_opt_many_args() {
            std::string error_message = cout("'Fusion/Controllers/Route::Get()' second parameter too much context");
            Php::out << error_message << std::flush;
            Php::error << "" << std::flush;
        }
    };
}