#pragma once

#include <string>
#include <fstream>
#include <iostream>

Php::Value minifier(std::string resource_character) {


    size_t resource_character_size = resource_character.size();   

    bool html_phar_tag = false;
    // bool space_annot = false;
    std::string minified_code;

    for(int index_character = 0; (size_t)index_character < resource_character_size; index_character++) {

        // const char iterate_char_prev = resource_character[index_character-1];
        const char iterate_char      = resource_character[index_character];
        // const char iterate_char_next = resource_character[index_character+1];

        if(!html_phar_tag && iterate_char == '>') {
            html_phar_tag = true;
            minified_code += iterate_char;
            continue;
        }

        if(html_phar_tag && iterate_char == '<') {
            html_phar_tag = false;
            minified_code += iterate_char;
            continue;
        }

        if(html_phar_tag && (iterate_char == ' ' || iterate_char == '\n')) {
            continue;
        } else {
            html_phar_tag = false;
        }

        if(iterate_char != '\n')
            minified_code += iterate_char;

    }
    
    return minified_code;
}