
#include <iostream>
#include <vector>

int main() {
    std::string foo = "hello/:get";

    std::vector<std::string> tmp = {""};

    for(auto &e : foo) {
        if(std::string(1, e) != "/") {
            tmp[tmp.size() - 1] += e;
        } else {
            tmp.push_back("");
        }
    }

    // for(auto &x : tmp)
        // for(auto &y : tmp)
            std::cout << tmp.size() << std::endl;

    return 0;
}