#pragma once

#include <phpcpp.h>

#include <iostream>

#include <fusion/database/core.cpp>

class Engine : public Php::Base {
    public: void static Foo() {
        Database::set::string({"hello_worldk", "foo", "bar"}, "hello world");
    }   

    public: Php::Value static Bar() {
        Php::Value doo = Database::get::string({"hello_worldk", "foo", "bar"});
        return doo;
    }

    public: void static Hapus() {
        Database::unset({"hello_worldk"});
    }
};