#pragma once

#include <phpcpp.h>

class Request : public Php::Base {
    public: Php::Value Foo() {
        return "oke";
    }
};