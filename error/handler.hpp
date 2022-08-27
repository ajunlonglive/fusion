#pragma once

#include <phpcpp.h>
#include <iostream>

#pragma once

#include <phpcpp.h>

#include <regex/wrapper/pcre2.hpp>

namespace error {
    void fusion_php_error_handler(Php::Parameters &param) {
        Php::Value error = Php::call("error_get_last");
        if (error["type"]) {
            Php::call("print_r", error);
        }
    }
}