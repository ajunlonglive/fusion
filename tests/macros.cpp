#include <iostream>

#define SET(set, req, method) set ? true : req == method ? true : false;

int main(void) {
    
    std::string str = "get";
    bool REQUEST_SET;

    std::string request_method = "GET";
    REQUEST_SET = SET(REQUEST_SET, request_method, "GET");
    REQUEST_SET = SET(REQUEST_SET, request_method, "POST");

    if(REQUEST_SET)
        std::cout << "oke siap" << std::endl;
    else
        std::cout << "ya salah" << std::endl;

    return 0;
}