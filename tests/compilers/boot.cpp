#include <iostream>
#include <fstream>

#include "minifier.hpp"
#include "subfix.hpp"
#include "keyword.hpp"

char character;
std::string compiled_code;
std::string temp_compiled_code;
std::string per_actual_keyword;
std::string per_actual_dynamic_keyword;

std::string reserv_prefix;
std::string reserv_suffix;

bool space_annot            = false;
bool html_phar_tag          = false;
int         i_open_minim_phar    = 0;
std::string s_open_minim_phar    = "";
std::string s_args_brace_phar    = "";
std::string b_open_minim_phar    = "false";
std::string b_open_minim_dynamic = "false";

int c_code_length = 0;

bool used_other_serv = false;

int main() {
    // Add file to stream and buffer to memory
    std::ifstream resource_code("file.php");
    std::string resource_character( (std::istreambuf_iterator<char>(resource_code)), (std::istreambuf_iterator<char>()) );

    // Adding white-space pre-content
    resource_character = " " +resource_character+ " ";
    
    // Iterate each character from resource_character
    for(int index_character = 0; index_character < resource_character.size(); index_character++) {

        if(index_character < c_code_length) continue;

        std::string per_actual_keyword = "";
        int token_keyword_length = 0;
        character = resource_character[index_character];

        if(b_open_minim_phar == "found")
            b_open_minim_phar = "false";  

        serfix::keyword::pair(index_character, resource_character, &i_open_minim_phar, 
                            &b_open_minim_phar, &s_open_minim_phar, &b_open_minim_dynamic, &s_args_brace_phar,
                            &token_keyword_length, &per_actual_keyword, &per_actual_dynamic_keyword);

        // Check if subfix between reserved keyword is not meet conditional
        serfix::subfix(resource_character, index_character, token_keyword_length, [&](bool prefix, bool suffix) {
            //
            if(b_open_minim_phar    == "found") return;
            //
            if(b_open_minim_dynamic == "found") return;

            //
            if(token_keyword_length > 0 && ( !prefix || !suffix )) {
                per_actual_keyword = "";
                token_keyword_length = 0;
                return;
            }
        });

        // Increment the raw code length after parsing in keyword function
        c_code_length += token_keyword_length;

        // Modify current compiled_code and add new actual_keyword from parsing translation
        if(b_open_minim_dynamic == "false" || b_open_minim_dynamic == "pre") {
            //
            compiled_code += per_actual_keyword;
        } else if(b_open_minim_dynamic == "found") {
            //
            temp_compiled_code += per_actual_dynamic_keyword;
            //
            compiled_code += per_actual_keyword;
            //
            compiled_code += temp_compiled_code;    
            //
            temp_compiled_code = "";
            //
            b_open_minim_dynamic = "false";
        } else {
            //
            temp_compiled_code += per_actual_keyword;
        }

        // If current index_character less than c_code_length, dont give access to char modifier which else, continue to next loop
        if(index_character < c_code_length) continue;

        // Increment length of compiled code for used another method
        c_code_length++;

        if(b_open_minim_dynamic == "false" || b_open_minim_dynamic == "pre") {
            // When given char is not begin and end of length, buffering to memory
            // First and last char must be escaped, use compare to meet the condition
            if(index_character != 0 && index_character+1 < resource_character.size()) {
                    compiled_code += character;
            }   
        } else {
            temp_compiled_code += character;
        }
        
    }
    
    compiled_code += temp_compiled_code;

    std::cout << "\n\n" << std::endl;
    std::cout << compiled_code << std::endl;

    return (int)false;
}