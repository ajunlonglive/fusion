#include <string>
#include <fstream>
#include <iostream>

int main() {

    std::ifstream resource_code("file.php");
    std::string resource_character( (std::istreambuf_iterator<char>(resource_code)), (std::istreambuf_iterator<char>()) );

    size_t resource_character_size = resource_character.size();   

    bool html_phar_tag = false;
    bool space_annot = false;
    int new_line    = 0;
    std::string minified_code;

    for(int index_character = 0; (size_t)index_character < resource_character_size; index_character++) {

        // const char iterate_char_prev = resource_character[index_character-1];
        const char iterate_char      = resource_character[index_character];
        const char iterate_char_next = resource_character[index_character+1];

        if(!html_phar_tag && iterate_char == '>') {
            html_phar_tag = true;
            new_line++;
            minified_code += iterate_char;
            continue;
        }

        if(html_phar_tag && iterate_char == '<') {
            html_phar_tag = false;
            new_line++;
            if(new_line > 150) {
                minified_code += '\n';
                new_line = 0;
            }
            minified_code += iterate_char;
            continue;
        }

        if(html_phar_tag && (iterate_char == ' ' || iterate_char == '\n')) {
            continue;
        } else {
            html_phar_tag = false;
        }

        if(iterate_char != '\n') {
            new_line++;
            minified_code += iterate_char;
        }

        // std::cout << new_line << " " << iterate_char << "" << iterate_char_next << std::endl;
        // if(new_line > 170 && new_line < 200 && iterate_char == '>' && iterate_char_next == '<') {
        //     minified_code += '\n';
        //     new_line = 0;
        // }

    }
    
    std::cout << minified_code << std::endl;

    return (int)false;
}