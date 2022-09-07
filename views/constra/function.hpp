#pragma once

#include <string>
#include <iostream>

#include <phpcpp.h>

#include "compiler/minifier.hpp"

#include <views/constra/compiler/utils.hpp>

namespace views {
namespace constra {


Php::Value f_minifier(Php::Parameters &param) {
    std::string content = (Php::Value)param[0];
    
    return views::constra::compiler::f_minifier(content);
}

Php::Value f_e(Php::Parameters &param) {
    Php::Value params = param;
    Php::Value content = params[params.size() - (size_t)1];

    std::vector<std::string> actual_params;
    for(auto &item : params)
        if(item.first < (int)(params.size() - (size_t)1))
            content = Php::call(item.second, content).stringValue();

    return content;
}


} }