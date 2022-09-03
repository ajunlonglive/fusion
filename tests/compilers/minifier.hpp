#pragma once

#include <string>

namespace compiler {
    bool minifier(char iterate_char, bool used_other_serv, bool *html_phar_tag, bool *space_annot, int c_code_length, std::string *resource_character) {
        /**
         * @brief 
         * 
         */
        if(c_code_length % 90 == 0) {
            *resource_character += "\n";
        }
        
        /**
         * @brief 
         * 
         */
        if(!used_other_serv && iterate_char == '\n') {
            return false;
        }

        /**
         * @brief 
         * 
         */
        if(!*html_phar_tag && iterate_char == '>') {
            *html_phar_tag = true;
            return true;
        }

        if(*html_phar_tag && iterate_char != '<' && iterate_char != ' ') {
            *html_phar_tag = false;
            return true; 
        }

        if(*html_phar_tag && iterate_char == '<') {
            *html_phar_tag = false;
            return true; 
        }

        /**
         * @brief 
         * 
         */
        if(!*html_phar_tag) {
            if(!*space_annot && iterate_char != ' ') {
                return true;
            }

            if(!*space_annot && iterate_char == ' ') {
                *space_annot = true;
                return true;
            }

            if(*space_annot && iterate_char != ' ') {
                *space_annot = false;
                return true; 
            }
        }

        return false;
    }
}