#pragma once

#include <string>

namespace serfix {
    bool minifier(char prefix, char *iterate_char, char suffix, bool used_other_serv, bool *html_phar_tag,
                  bool *space_annot, int c_code_length, std::string *compiled_code) {
        /**
         * @note Limit length per line to 90 char, else with break line and continue the content
         * 
         */

        if((*compiled_code).length() % 80 == 0) {
            *compiled_code += "\n";
        }

        /**
         * @note 
         * 
         */
        if(used_other_serv) {
            if(*iterate_char == '\n') {
                if(prefix != ' ' || suffix != ' ')
                    *iterate_char = ' ';
                    
                return true;
            }

            if(!*space_annot && *iterate_char != ' ') {
                return true;
            }

            if(!*space_annot && *iterate_char == ' ') {
                *space_annot = true;
                return true;
            }

            if(*space_annot && *iterate_char != ' ') {
                *space_annot = false;
                return true; 
            }
        }

        /**
         * @note 
         * 
         */
        if(*iterate_char == '\n') {
            return false;
        }

        /**
         * @note Check if html phar is found "<...>actual content<...>"
         * 
         */
        if(!*html_phar_tag && *iterate_char == '>') {
            *html_phar_tag = true;
            return true;
        }

        if(*html_phar_tag && *iterate_char != '<' && *iterate_char != ' ') {
            *html_phar_tag = false;
            return true; 
        }

        if(*html_phar_tag && *iterate_char == '<') {
            *html_phar_tag = false;
            return true; 
        }

        /**
         * @brief 
         * 
         */
        if(!*html_phar_tag) {
            if(!*space_annot && *iterate_char != ' ') {
                return true;
            }

            if(!*space_annot && *iterate_char == ' ') {
                *space_annot = true;
                return true;
            }

            if(*space_annot && *iterate_char != ' ') {
                *space_annot = false;
                return true; 
            }
        }

        return false;
    }
}