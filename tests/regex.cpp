#include <regex/wrapper/pcre2.hpp>
#include <iostream>


int main() {
    regexp::match("(?<open>sultan)|(?<close>acong$)", "sultan sama kamu itu sudah gila, acong", [&](const char *matched) {
        std::cout << matched << std::flush;
    });
    
    return 0;
}