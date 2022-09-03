#include <iostream>

void change(std::string *stringf) {
    *stringf = "true";
}

int main() {
    std::string test;

    test = "bebe";

    change(&test);

    std::cout << test << std::endl;

    return 0;
}