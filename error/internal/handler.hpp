#pragma once

#include <phpcpp.h>

#include <transport/session/session.hpp>

#include <iostream>

namespace error {
    namespace internal {
        class error_handler : public Php::Base {
            public: void static callback(Php::Parameters &param) {
                if(!param[0])
                    return void();

                Php::Value function_name = param[0];
        
                // Php::out << function_name << " <- function name" << std::flush;

                transport::session::c_set::m_string({"FUSION_STORE", "FS_ERROR", "Php_Error_Handler_Function"}, function_name);
            }
        };
    }
}