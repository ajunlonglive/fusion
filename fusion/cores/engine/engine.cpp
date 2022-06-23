#pragma once

#include <phpcpp.h>

#include <iostream>

#include <fusion/database/core.cpp>

class Engine : public Php::Base {
    public: Engine() {}
    public: virtual ~Engine() {}
    public: void static Framework() {
        Php::Value arr_list;
        arr_list["foo"] = "bar?";
        arr_list["bar"] = "foo?";

        Database::set::array({"Hello", "Guys"}, arr_list);
        Php::Value get_arr_list = Database::get::array({"Hello", "Guys"});
        Php::out << get_arr_list["foo"] << " yes " << std::flush;
    }

};