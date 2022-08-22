#pragma once

#include <phpcpp.h>

#include <string>

std::string str_repeat(std::string value, int notation) {
    std::string buffer;
    for(int i = 0; i < notation; i++)
        buffer += value;
    
    return buffer;
}


std::string array_parser(Php::Value array, int nbsp_space = 0) {
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
            buffer += "<details open style=\"margin-left: " +spaceheader+ "px;\"><summary><span>object(" +array_type+ ") (" +Php::count(array).stringValue()+ ")</span> {</summary>";
    } else {
        buffer += "<details open style=\"margin-left: " +spaceheader+ "px;\"><summary><span>array(" +Php::count(array).stringValue()+ ")</span> (</summary>";
    }

    for(auto &arrays : array) {
        if(Php::call("is_array", arrays.second).boolValue() || Php::call("is_object", arrays.second).boolValue()) {
            buffer += array_parser(arrays.second, 30);
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

// std::string array_parser(Php::Value array, int nbsp_space = 4) {
//     std::string buffer;
//     std::string array_type;
    
//     // Php::eval("function cast_object_array($obj) { $res = (array) $obj; return $res; }");

//     if(!Php::is_array(array)) {
//         array_type = Php::call("get_class", array).stringValue();
//     }

//     if(!Php::is_array(array)) {
//         array = Php::call("get_object_vars", array);
//         if(array_type == "stdClass")
//             buffer += str_repeat("&nbsp;", nbsp_space - 4) + "<span style=\"background: green; color: yellow;\">object(stdClass) (" +Php::count(array).stringValue()+ ")</span> {<br />";
//         if(array_type != "stdClass")
//             buffer += str_repeat("&nbsp;", nbsp_space - 4) + "<span style=\"background: green; color: yellow;\">object(" +array_type+ ") (" +Php::count(array).stringValue()+ ")</span> {<br />";
//     } else {
//         buffer += str_repeat("&nbsp;", nbsp_space - 4) + "<span style=\"background: green; color: yellow;\">array(" +Php::count(array).stringValue()+ ")</span> (<br />";
//     }

//     for(auto &arrays : array) {
//         if(Php::call("is_array", arrays.second).boolValue() || Php::call("is_object", arrays.second).boolValue()) {
//             buffer += array_parser(arrays.second, nbsp_space + 12);
//         } else {
//             buffer += str_repeat("&nbsp;", nbsp_space)+ "<span style=\"background: red; color: black;\">[" +(std::string)arrays.first+ "] => " +(std::string)arrays.second+ "</span><br />";
//         }
//     }

//     if(Php::call("is_object", array)) {
//         buffer += str_repeat("&nbsp;", nbsp_space - 4)+ "}<br />";
//     } else {
//         buffer += str_repeat("&nbsp;", nbsp_space - 4)+ ")<br />";
//     }

//     return buffer;
// }

void cd(Php::Parameters &param) {
    Php::Value main_data = param[0];

    if(Php::call("is_null", main_data).boolValue()) {
        Php::out << "<span style=\"background: #000000; color: yellow;\">(null) " << main_data << "</span>" << std::flush;
    }
    
    if(Php::call("is_string", main_data).boolValue()) {
        Php::out << "<span style=\"background: #000000; color: yellow;\">(string) " << main_data << "</span>" << std::flush;
    }

    if(Php::call("is_int", main_data).boolValue()) {
        Php::out << "<span style=\"background: #000000; color: yellow;\">(int) " << main_data << "</span>" << std::flush;
    }

    if(Php::call("is_array", main_data).boolValue() || Php::call("is_object", main_data).boolValue()) {
        Php::out << array_parser(main_data) << std::flush;
    } 
}

