#include <iostream>
#include <fstream>

#include "minifier.hpp"

char character;
std::string compiled_code;

bool space_annot    = false;
bool html_phar_tag  = false;

int c_code_lenght;

int main() {
    // Add file to stream and buffer to memory
    std::ifstream resource_code("file.php");
    std::string resource_character( (std::istreambuf_iterator<char>(resource_code)), (std::istreambuf_iterator<char>()) );

    // Adding space pre-content
    resource_character += " ";
    
    // Iterate each character from resource_character
    for(int index_character = 0; index_character < resource_character.size(); index_character++) {
        character = resource_character[index_character];

        // Escape double white-space and break-line
        if(compiler::minifier(character, false, &html_phar_tag, &space_annot, c_code_lenght, &compiled_code)) {
            // Increment length of compiled code for used another method
            c_code_lenght++;
            // When given char is not two of them, buffering to memory
            compiled_code += character;
        }
    }

    std::cout << c_code_lenght << std::endl;
    std::cout << compiled_code << std::endl;

    return (int)false;
}