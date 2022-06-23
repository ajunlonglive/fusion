#pragma once

#include <includes.h>

#include <iostream>
#include <vector>

namespace Database {
    class set;
    class get;
    void unset();
}

class Database::set : public Php::Base {
    public: void static string(std::vector<std::string> array_index, std::string value) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }

        Php::eval("$_SESSION" +merge_array_index+ " = '" +value+ "';");
    }

    public: void static number(std::vector<std::string> array_index, double value) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }   

        Php::eval("$_SESSION" +merge_array_index+ " = " +std::to_string(value)+ ";");
    }

    public: void static array(std::vector<std::string> array_index, Php::Value value) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }   
        
        std::string string_array_value = Php::call("json_encode", value); 

        Php::eval("$_SESSION" +merge_array_index+ " = json_decode('" +string_array_value+ "', true);");
    }
};

class Database::get : public Php::Base {
    public: std::string static string(std::vector<std::string> array_index) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }

        Php::Value ret_from_eval = Php::eval("return $_SESSION" +merge_array_index+ ";").stringValue();
        std::string s_ret_from_eval = ret_from_eval;
        
        return s_ret_from_eval;
    }

    public: double static number(std::vector<std::string> array_index) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }

        Php::Value ret_from_eval = Php::eval("return $_SESSION" +merge_array_index+ ";").floatValue();
        
        return ret_from_eval;
    }

    public: Php::Value static array(std::vector<std::string> array_index) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }

        Php::Value ret_from_eval = Php::eval("return json_encode($_SESSION" +merge_array_index+ ");").stringValue();
        Php::Value conv_ret_from_eval = Php::call("json_decode", ret_from_eval, true);
        
        return conv_ret_from_eval;
    }
};

void unset(std::vector<std::string> array_index) {
    std::string merge_array_index = "";
    
    for(auto &index: array_index) {
        merge_array_index += "['" +index+ "']";
    }

    Php::eval("unset($_SESSION" +merge_array_index+ ");");
};