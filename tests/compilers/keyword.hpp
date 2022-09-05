#pragma once

#include <string>
#include <vector>

std::vector<std::string> reserved_keyword = {
    "%php",
    "%ephp",
};

std::vector<std::string> actual_keyword = {
    "<?php",
    "?>",
};

namespace serfix {
    namespace keyword {
        void pair(int index_iterate_char, std::string resource_character, int *token_keyword_length, std::string *per_actual_keyword) {
            for(int i_revkey = 0; i_revkey < reserved_keyword.size(); i_revkey++) {
                std::string per_word_of_keyrev = reserved_keyword[i_revkey];

                for(int i_char_revkey = 0; i_char_revkey < per_word_of_keyrev.size(); i_char_revkey++) {
                    const char per_char_of_keyrev = reserved_keyword[i_revkey][i_char_revkey];
                    const char per_char_of_source = resource_character[index_iterate_char + i_char_revkey];

                    if(per_char_of_keyrev == per_char_of_source) {
                        int current_token = *token_keyword_length;
                        *token_keyword_length += 1;
                    } else {
                        *token_keyword_length = 0;
                        break;
                    }

                }   
                
                if(*token_keyword_length > 0) {
                    *per_actual_keyword = actual_keyword[i_revkey];
                    break;
                }

            }
        }
    }
}