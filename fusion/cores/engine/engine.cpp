#include <phpcpp.h>
#include <iostream>

class Engine : public Php::Base {
    public: void static Foo() {
        Php::out << "test" << std::flush;
    }   
};