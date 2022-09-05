#include <iostream>
#include <fstream>

#include "minifier.hpp"
#include "subfix.hpp"
#include "keyword.hpp"

char character;
std::string compiled_code;
std::string per_actual_keyword;

std::string reserv_prefix;
std::string reserv_suffix;

bool space_annot            = false;
bool html_phar_tag          = false;
int  dim_constra_phar_tag   = 0;

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
        
        std::string per_actual_keyword   = "";
        int         token_keyword_length = 0;
        int         token_actual_length  = 0;
                    character            = resource_character[index_character];
        

        serfix::keyword::pair(index_character, resource_character, &token_keyword_length, &per_actual_keyword);

        serfix::subfix(resource_character, index_character, token_keyword_length, [&](bool prefix, bool suffix) {
            if(token_keyword_length > 0 && !prefix) {
                per_actual_keyword = "";
                token_keyword_length = 0;
                return;
            }

            if(token_keyword_length > 0 && !suffix) {
                per_actual_keyword = "";
                token_keyword_length = 0;
                return;
            }

            if(token_keyword_length > 0) {
                /**
                 * @note Chec if Constra syntax if found <<syntax... actual content >>syntax...
                 * 
                 */
                if(resource_character[index_character] == '%') {
                    if(dim_constra_phar_tag > 0 && resource_character[index_character + 1] == 'e') {
                        dim_constra_phar_tag -= 1;
                    } else {
                        dim_constra_phar_tag += 1;
                    }
                }
            }
        });

        if(dim_constra_phar_tag > 0) { 
            used_other_serv = true;
        } else {
            used_other_serv = false;
        }

        c_code_length += token_keyword_length;
        compiled_code += per_actual_keyword;

        if(index_character < c_code_length) continue;

        // Increment length of compiled code for used another method
        c_code_length++;

        // Escape double white-space and break-line
        if(serfix::minifier(resource_character[index_character > 0 ? index_character-1 : 0], 
        &character, resource_character[index_character > 0 ? index_character+1 : 0],
        used_other_serv, &html_phar_tag, &space_annot, c_code_length, &compiled_code)) {
            
            // When given char is not two of them, buffering to memory
            // First and last char must be escaped, use compare if else thrown null char
            if(index_character != 0 && index_character+1 < resource_character.size()) {
                compiled_code += character;
            }
            
            // compiled_code += index_character == 0 ? (char)0 : index_character+1 < resource_character.size() ? character : (char)0;
        }

    }
    
    // std::cout << "\n\n" << std::endl;
    std::cout << compiled_code << std::endl;

    return (int)false;
}