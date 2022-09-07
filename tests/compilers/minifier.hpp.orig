#pragma once

#include <string>


// int  dim_constra_phar_tag   = 0;
// bool used_other_serv = false;

// // Set used_other_serv to notifier HTML minifier for enabled/disabled minifier.
// used_other_serv = dim_constra_phar_tag > 0 ? true : false;

// if(serfix::minifier(resource_character[index_character > 0 ? index_character-1 : 0], 
// &character, resource_character[index_character > 0 ? index_character+1 : 0],
// used_other_serv, &html_phar_tag, &space_annot, c_code_length, &compiled_code)) {

// if(token_keyword_length > 0) {
//     // Check if Constra alias templating engine syntax if found <<syntax... actual content >>syntax...
//     if(resource_character[index_character] == '%') {
//         if(dim_constra_phar_tag > 0 && resource_character[index_character + 1] == 'e') {
//             dim_constra_phar_tag -= 1;
//         } else {
//             dim_constra_phar_tag += 1;
//         }
//     }
// }

namespace serfix {
    bool minifier(char prefix, char *iterate_char, char suffix, bool used_other_serv, bool *html_phar_tag,
                  bool *space_annot, int c_code_length, std::string *compiled_code) {
        /**
         * @note Limit length per line to 90 char, else with break line and continue the content
         * 
         */
        // std::cout << (*compiled_code).length() << std::endl;
        // if((*compiled_code).length() % 80 == 0) {
        //     *compiled_code += "\n";
        // }

        /**
         * @note 
         * 
         */
        if(used_other_serv) {
            if((*iterate_char) == '\n') {
                if(prefix != ' ' || suffix != ' ') {
                    return false;
                }
                return true;
            }

            if(!(*space_annot) && (*iterate_char) != ' ') {
                return true;
            }

            if(!(*space_annot) && (*iterate_char) == ' ') {
                *space_annot = true;
                return true;
            }

            if((*space_annot) && (*iterate_char) != ' ') {
                *space_annot = false;
                return true; 
            }
        }

        /**
         * @note 
         * 
         */
        if((*iterate_char) == '\n') {
            return false;
        }

        /**
         * @note Check if html phar is found "<...>actual content<...>"
         * 
         */
        if(!(*html_phar_tag) && (*iterate_char) == '>') {
            *html_phar_tag = true;
            return true;
        }

        if((*html_phar_tag) && (*iterate_char) != '<' && (*iterate_char) != ' ') {
            *html_phar_tag = false;
            return true; 
        }

        if((*html_phar_tag) && (*iterate_char) == '<') {
            *html_phar_tag = false;
            return true; 
        }

        /**
         * @brief 
         * 
         */
        if(!(*html_phar_tag)) {
            if(!(*space_annot) && (*iterate_char) != ' ') {
                return true;
            }

            if(!(*space_annot) && (*iterate_char) == ' ') {
                *space_annot = true;
                return true;
            }

            if((*space_annot) && (*iterate_char) != ' ') {
                *space_annot = false;
                return true; 
            }
        }

        return false;
    }
}