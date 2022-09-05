#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> reserved_keyword = {
    "%php",
    "%ephp",

    "%if",
    "%else",
    "%eif",
    
    "%for",
    "%efor",

    " as ",
};

std::unordered_map<std::string, std::string> dynamic_reserved_keyword;

std::vector<std::string> actual_keyword = {
    "<?php",
    "?>",

    "<?php if",
    "<?php else; ?>",
    "<?php endif; ?>",

    "<?php for",
    "} ?>",
};

std::unordered_map<std::string, std::string> phar_keyword;

namespace serfix {
    namespace keyword {
        void pair(int index_iterate_char, std::string resource_character, int *i_open_minim_phar, std::string *b_open_minim_phar, std::string *s_open_minim_phar, bool *b_open_minim_dynamic, int *token_keyword_length, std::string *per_actual_keyword, std::string *per_actual_dynamic_keyword) {
            
            phar_keyword["%if"]  = "): ?>";
            phar_keyword["%for"] = ") { ?>";

            dynamic_reserved_keyword["%for"] = "each";

            const char character = resource_character[index_iterate_char];
            
            if( (*b_open_minim_phar) == "true" && ( character == '(' || character == ')' )) {
                    if(resource_character[index_iterate_char] == '(') {
                        *i_open_minim_phar += 1;
                    }   

                    if(resource_character[index_iterate_char] == ')') {
                        *i_open_minim_phar -= 1;

                        if((*i_open_minim_phar) < 1) {
                            *per_actual_keyword       = phar_keyword[(*s_open_minim_phar)];
                            *token_keyword_length     = 1;
                            *b_open_minim_phar        = "found";
                        }
                    }


                return void();
            }

            for(int i_revkey = 0; i_revkey < reserved_keyword.size(); i_revkey++) {
                std::string per_word_of_keyrev = reserved_keyword[i_revkey];

                for(int i_char_revkey = 0; i_char_revkey < per_word_of_keyrev.size(); i_char_revkey++) {
                    const char per_char_of_keyrev = per_word_of_keyrev[i_char_revkey];
                    const char per_char_of_source = resource_character[index_iterate_char + i_char_revkey];
                   


                    if(per_char_of_keyrev == per_char_of_source) {
                        *token_keyword_length += 1;
                    } else {      
                        *token_keyword_length = 0;
                        break;
                    }

                }   
                
                if(*token_keyword_length > 0) {

                    if((*b_open_minim_dynamic) && dynamic_reserved_keyword.find(reserved_keyword[i_revkey]) != dynamic_reserved_keyword.end()) {
                        *per_actual_keyword = dynamic_reserved_keyword[reserved_keyword[i_revkey]];
                        *per_actual_dynamic_keyword = reserved_keyword[i_revkey];
                        *b_open_minim_dynamic = false;

                        break;
                    }

                    *per_actual_keyword = actual_keyword[i_revkey];
                    
                    if((*b_open_minim_phar) == "false" && phar_keyword.find(reserved_keyword[i_revkey]) != phar_keyword.end()) {
                        *s_open_minim_phar = reserved_keyword[i_revkey];
                        *b_open_minim_phar = "true";
                    }

                    if(dynamic_reserved_keyword.find(reserved_keyword[i_revkey]) != dynamic_reserved_keyword.end()) {
                        *b_open_minim_dynamic = true;
                    }

                    break;
                }

            }
        }
    }
}