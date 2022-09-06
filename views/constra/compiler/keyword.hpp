#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "utils.hpp"

namespace serfix {
    namespace keyword {
        void pair(int index_iterate_char, std::string resource_character, int *i_open_minim_phar,
                std::string *b_open_minim_phar, std::string *s_open_minim_phar, std::string *b_open_minim_dynamic, std::string *s_args_brace_phar,
                int *token_keyword_length, std::string *per_actual_keyword, std::string *per_actual_dynamic_keyword) {
            
            // std::vector<std::string> reserved_keyword = {
            //     "{{",
            //     "}}",
            //     "%php",
            //     "%ephp",

            //     "%if",
            //     "%else",
            //     "%eif",
                
            //     "%for",
            //     "%efor",

            //     // Char pair for trigger of dynamic reserved keyword
            //     // Not actually reserved_keyword to actual_keyword
            //     " as ",
            // };

            std::vector<std::string> reserved_keyword = {
                "<%e ",
                "<%e>",
                "</%e>",
                "<%php>",
                "</%php>",

                "<%if",
                "<%else>",
                "</%if>",
                
                "<%for",
                "</%for>",

                // Char pair for trigger of dynamic reserved keyword
                // Not actually reserved_keyword to actual_keyword
                " as ",
            };

            // std::vector<std::string> dynamic_reserved_keyword_list = {
            //     "%for",
            // };

            std::vector<std::string> dynamic_reserved_keyword_list = {
                "<%for",
            };

            std::unordered_map<std::string, std::string> args_brace_echos;

            std::unordered_map<std::string, std::string> dynamic_reserved_keyword;

            std::vector<std::string> actual_keyword = {
                "<?php echo e(",
                "<?php echo e(",
                "); ?>",
                "<?php ",
                " ?>",

                "<?php if",
                "<?php else: ?>",
                "<?php endif; ?>",

                "<?php for",
                "<?php } ?>",

                // Char pair for trigger of dynamic reserved keyword
                // Not actually reserved_keyword to actual_keyword
                " as ",
            };

            std::unordered_map<std::string, std::string> phar_keyword;

            // phar_keyword["%if"]  = "): ?>";
            // phar_keyword["%for"] = ") { ?>";

            phar_keyword["<%if"]  = "): ?";
            phar_keyword["<%for"] = ") { ?";

            dynamic_reserved_keyword[" as "] = "each";

            // args_brace_echos["{{"] = "}}";
            // args_brace_echos["<e>"] = "</e>";
            // args_brace_echos["<e "] = "</e>";
            args_brace_echos["<%e "] = "</%e>";

            std::unordered_map<std::string, std::string> act_brace_char_phar;
            // act_brace_char_phar["|"] = ",";
            act_brace_char_phar[" "] = ",";
            act_brace_char_phar[">"] = ",";

            // std::unordered_map<std::string, std::string> d_act_brace_char_phar;
            // d_act_brace_char_phar[" >"] = ",";

            const char character = resource_character[index_iterate_char];

            if( (*s_args_brace_phar) != "" && 
                array_key_exists(act_brace_char_phar, std::string(1, resource_character[index_iterate_char-1])) &&
                array_key_exists(act_brace_char_phar, std::string(1, resource_character[index_iterate_char])) ) {
                    *token_keyword_length = 1;
                return void();
            }

            // When args_brace_phar is active, find the delimiter to actual replace keyword
            if( (*s_args_brace_phar) != "" && 
                !array_key_exists(act_brace_char_phar, std::string(1, resource_character[index_iterate_char-1])) &&
                array_key_exists(act_brace_char_phar, std::string(1, resource_character[index_iterate_char])) ) {
                *per_actual_keyword = act_brace_char_phar[std::string(1, resource_character[index_iterate_char])];
                *token_keyword_length += (*per_actual_keyword).length();
                return void();
            }

            // When open_minim_phar is active, find the open and close phar to increase/decrement the current lenght of phar specific keyword
            // open_minim_phar can be use too for anonther events, such as dynamic reserved keyword to find trigger keyword
            if( (*b_open_minim_phar) == "true" && ( character == '(' || character == ')' )) {
                    // If the current char if open phar
                    if(resource_character[index_iterate_char] == '(') {

                        // When the current of phar length is still 0, meaning the first open phar meet
                        // But also it can be open_minim_dynamic of reserved_keyword
                        // For the reason, changed to open_minim_dyanmic to true for finding the trigger keyword
                        if((*i_open_minim_phar) < 1 && (*b_open_minim_dynamic) == "pre") {
                            // set open_minim_dynamic to true
                            *b_open_minim_dynamic = "true";
                        }

                        // Increase the phar length of open_minim_phar because found open phar
                        *i_open_minim_phar += 1;
                    }   

                    // if(resource_character[index_iterate_char] == ')>') {
                    // If the current char if close phar
                    std::string test(1, resource_character[index_iterate_char]);
                    test += resource_character[index_iterate_char + 1];
                    if(test == ")>") {
                        // Decrease the phar length of open_minim_phar because found close phar
                        *i_open_minim_phar -= 1;

                        // When the current phar length decreased to 0, meaning the last of close phar meet
                        // It mean also of end to find the trigger keyword which is, it can't be found
                        // Reset again open_minim_phar to default and tell boot loader to merge current 2 temporate compiled code
                        // Also add per_actual_dynamic_keyword from open_minim_phar
                        if((*i_open_minim_phar) < 1) {
                            // e.g. "): ?>"
                            *per_actual_dynamic_keyword = phar_keyword[(*s_open_minim_phar)];
                            // Change token_keyword_length to 1
                            *token_keyword_length = 1;
                            // Change to found for telling boot loader
                            *b_open_minim_phar = "found";
                            // Change to found for telling boot loader
                            *b_open_minim_dynamic = "found";
                        }
                    }

                // Break the flow of code
                return void();
            }

            // The default reserved keyword along aside another events run
            // Will iterate each reserved keyword until same as char and length of keyword
            for(int i_revkey = 0; (size_t)i_revkey < reserved_keyword.size(); i_revkey++) {
                std::string per_word_of_keyrev = reserved_keyword[i_revkey];

                // Will iterate each char of keyword
                for(int i_char_revkey = 0; (size_t)i_char_revkey < per_word_of_keyrev.size(); i_char_revkey++) {
                    const char per_char_of_keyrev = per_word_of_keyrev[i_char_revkey];

                    // Change the char of resource of code based iteration of reserved_keyword
                    const char per_char_of_source = resource_character[index_iterate_char + i_char_revkey];

                    // If char of keyword same as iterate char of resource code continue the loop to next char or resource code
                    // And also increase the token_keyword_length too
                    if(per_char_of_keyrev == per_char_of_source) {
                        *token_keyword_length += 1;
                    
                    // But if not same, it will tell to break current iteration char of keyword, to the next reserved_keyword
                    // And reset token_keyword_length too
                    } else {      
                        // Reset token_keyword_length
                        *token_keyword_length = 0;
                        // Break the flow of iteration per char reserved_keyword
                        break;
                    }

                }   
                
                // When token_keyword_length greater than 0, it mean the reserved_keyword found
                if(*token_keyword_length > 0) {

                    // When open_minim_dynamic is active, it will find the trigger keyword
                    // The trigger keyword saved to reserved_keyword, it actually not use for such replacement actual_keyword
                    // The reason is for decrease iteration notation, that why it has same actual_keyword with reserved_keyword
                    // But if the keyword found, it will add per_actual_keyword to suffix of current code_compiled (the dynamic keyword bassed trigger)
                    // And adding the trigger keyword to suffix of current temp_compiled_code
                    if((*b_open_minim_dynamic) == "true" && array_key_exists(dynamic_reserved_keyword, reserved_keyword[i_revkey])) {
                        // e.g. "each" => " as "
                        *per_actual_keyword = dynamic_reserved_keyword[reserved_keyword[i_revkey]];

                        // e.g. " as " <= "each"
                        *per_actual_dynamic_keyword = reserved_keyword[i_revkey];

                        // Set param to found to tell boot loader for concacte 2 temporate result
                        *b_open_minim_dynamic = "found";
                    } else {
                        
                        // The actual keyword replacement, if events is not on going
                        // Alongside to per_actual_keyword changed, the address of token_keyword_length will be assigned
                        *per_actual_keyword = actual_keyword[i_revkey];
                        
                        /** -------------------------------- **/
                        // Pair args_brace_phar when meet the open phar
                        if((*s_args_brace_phar) == "" && array_key_exists(args_brace_echos, reserved_keyword[i_revkey])) {
                            *s_args_brace_phar = reserved_keyword[i_revkey];
                        }

                        // Reset args_brace_phar when meet the close phar
                        if((*s_args_brace_phar) != "" && args_brace_echos[(*s_args_brace_phar)] == reserved_keyword[i_revkey]) {
                            *s_args_brace_phar = "";
                        }
                        /** -------------------------------- **/

                        // open_minim_phar, check keyword if current keyword has a specific keyword assigned to open_minim_phar
                        // When the result was true, open_minim_phar changed to active, finding last closed phar
                        if((*b_open_minim_phar) == "false" && array_key_exists(phar_keyword, reserved_keyword[i_revkey])) {
                            *s_open_minim_phar = reserved_keyword[i_revkey];
                            *b_open_minim_phar = "true";
                        }

                        // open_minim_dynamic, check keyword if current keyword has a specific keyword assigned to open_minim_dynamic
                        // When the result was true, open_minim_dynamic changed to active, finding the trigger keyword
                        // The changed of open_minim_dynamic will effect to temporate compiled code result to temp_compiled_code
                        // It will make two result as is finding the trigger keyword, then if meet. The temporare will merge it again
                        if((*b_open_minim_dynamic) == "false" && in_array(dynamic_reserved_keyword_list, reserved_keyword[i_revkey])) {
                            *b_open_minim_dynamic = "pre";
                        }

                    }

                    // Break the flow iteration of per word reserved_keyword
                    break;
                }

            }
        }
    }
}