#pragma once

#include <phpcpp.h>

#include <iostream>

namespace error_page {
    class get {
        public: void static code_404() {
            Php::out << "404: Not Found (GET)" << std::flush;
        }
    };

    class post {
        public: void static code_404() {
            Php::out << "404: Not Found (POST)" << std::flush;
        }
    };
}