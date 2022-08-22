#include <iostream>


std::string str_repeat(std::string value, int notation) {
    std::string buffer;
    for(int i = 0; i < notation; i++)
        buffer += value;
    
    return buffer;
}

int main(void) {
    std::cout << str_repeat("test", 5) << std::endl;
}