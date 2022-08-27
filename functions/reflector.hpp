#pragma once

#include <phpcpp.h>

void reflector(Php::Parameters &param) {
    Php::Value object_function_name = param[0];
    Php::call("var_dump", object_function_name);
}