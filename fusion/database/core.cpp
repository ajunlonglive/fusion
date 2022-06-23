#pragma once

#include <phpcpp.h>

#include <iostream>
#include <vector>

namespace Database {
    class set;
    class get;
    class unset;
}

class Database::set : public Php::Base {
    public: void static string(std::vector<std::string> arr_index, std::string value) {
        std::string merge_arr_index = "";
        
        for(auto &index: arr_index) {
            merge_arr_index += "['" +index+ "']";
        }

        Php::eval("$_SESSION" +merge_arr_index+ " = '" +value+ "';");
    }
};

class Database::get : public Php::Base {
    public: std::string static string(std::vector<std::string> arr_index) {
        std::string merge_arr_index = "";
        
        for(auto &index: arr_index) {
            merge_arr_index += "['" +index+ "']";
        }

        Php::Value ret_from_eval = Php::eval("return $_SESSION" +merge_arr_index+ ";").stringValue();
        std::string s_ret_from_eval = ret_from_eval;
        
        return s_ret_from_eval;
    }
};

class Database::unset : public Php::Base {
    public: unset(std::vector<std::string> arr_index) {
        std::string merge_arr_index = "";
        
        for(auto &index: arr_index) {
            merge_arr_index += "['" +index+ "']";
        }

        Php::eval("unset($_SESSION" +merge_arr_index+ ");");
    }
};