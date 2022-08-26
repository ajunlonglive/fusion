#pragma once

#include <phpcpp.h>

#include <string>

std::string str_repeat(std::string value, int notation) {
    std::string buffer;
    for(int i = 0; i < notation; i++)
        buffer += value;
    
    return buffer;
}


std::string array_parser(Php::Value array, int nbsp_space = 0, std::string index_name = "") {
    std::string buffer;
    std::string array_type;
    std::string spaceheader;

    if((nbsp_space == 0)) {
        spaceheader = "0";
    } else {
        spaceheader = std::to_string(nbsp_space);
    }

    std::string spaceval = "30";

    if(!Php::is_array(array)) {
        array_type = Php::call("get_class", array).stringValue();
    }

    if(!Php::is_array(array)) {
        array = Php::call("get_object_vars", array);    
        if(array_type == "stdClass")
            buffer += "<details open style=\"margin-left: " +spaceheader+ "px;\"><summary><span>object(stdClass) (" +Php::count(array).stringValue()+ ")</span> {</summary>";
        if(array_type != "stdClass")
            buffer += "<details open style=\"margin-left: " +spaceheader+ "px;\"><summary><span>object(" +Php::count(array).stringValue()+ ") [" +array_type+ "]</span> {</summary>";
    } else {
        buffer += "<details open style=\"margin-left: " +spaceheader+ "px;\"><summary><span>array(" +Php::count(array).stringValue()+ ") [" +index_name+ "]</span> (</summary>";
    }

    for(auto &arrays : array) {
        if(Php::call("is_array", arrays.second).boolValue() || Php::call("is_object", arrays.second).boolValue()) {
            std::string index_name = arrays.first;
            buffer += array_parser(arrays.second, 30, index_name);
        } else {
            buffer += "<span style=\"margin-left: 30px; \">[" +(std::string)arrays.first+ "] => " +(std::string)arrays.second+ "</span><br />";
        }
    }

    if(Php::call("is_object", array)) {
        buffer += "}<br /></details>";
    } else {
        buffer += ")</details>";
    }

    return buffer;
}

void cd(Php::Parameters &param) {
    Php::Value main_data = param[0];

    if(Php::call("is_null", main_data).boolValue()) {
        Php::out << "(null) " << main_data << std::flush;
    }
    
    if(Php::call("is_string", main_data).boolValue()) {
        Php::out << "string (" +std::to_string(main_data.length())+ ") \"" << main_data << "\"" << std::flush;
    }

    if(Php::call("is_int", main_data).boolValue()) {
        Php::out << "int (" << main_data << ")" << std::flush;
    }

    if(Php::call("is_array", main_data).boolValue() || Php::call("is_object", main_data).boolValue()) {
        Php::out << array_parser(main_data) << std::flush;
    } 
}

