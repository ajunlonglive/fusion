#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


int main() {
    
    std::ifstream ifs("file.php");
    std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
    // std::cout << content[0] << std::endl;
    std::vector<std::string> keyword = {
        "%php",
        " %ephp",

        "{{",
        "}}",

        "%if", 
        "%else",
        "%eif",

        "%for",
        "%efor",
    };
    std::vector<std::string> act_keyword = {
        "<?php ",
        " ?>",

        "<?php echo ",
        " ?>",

        "<?php if", // %if
        "<?php else: ?>",
        "<?php endif; ?>",

        "<?php for",
        "<?php } ?>",
    };

    std::unordered_map<std::string, std::string> phar_keyword;
                            phar_keyword["%if"] = "): ?>";
                            phar_keyword["%for"] = ") { ?>";

    std::vector<std::string> dynamic_keyword = {"%for"};

    std::vector<std::string> token_dynamic_keyword = {
        " as ",
    };

    std::unordered_map<std::string, std::string> pattern_dynamic_keyword;
                            pattern_dynamic_keyword[" as "] = "each";


    int content_length = 0;

    std::string compiled_content = "";
    std::string temp_compiled_content = "";

    int open_phar_tracer = 0;

    std::string current_phar_keyword = "";

    std::string find_phar = "false";

    bool current_find_dynamic_keyword = false;

    for(std::size_t index_content = 0; index_content < content.size(); ++index_content) {
        if(index_content < content_length) continue;

        if(current_find_dynamic_keyword) {
            for(std::size_t index_token_dynamic_keyword = 0; index_token_dynamic_keyword < token_dynamic_keyword.size(); ++index_token_dynamic_keyword) {
                int index_token_dynamic_keyword_length = 0;

                for(std::size_t index_char_token_dynamic_keyword = 0; index_char_token_dynamic_keyword < token_dynamic_keyword[index_token_dynamic_keyword].size(); ++index_char_token_dynamic_keyword) {
                    if(token_dynamic_keyword[index_token_dynamic_keyword][index_char_token_dynamic_keyword] == content[content_length + index_char_token_dynamic_keyword]) {
                        index_token_dynamic_keyword_length++;
                    } else {
                        index_token_dynamic_keyword_length = 0;
                        break;
                    }
                }

                if(index_token_dynamic_keyword_length > 0) {
                    // content_length += index_token_dynamic_keyword_length;
                    compiled_content += pattern_dynamic_keyword[token_dynamic_keyword[index_token_dynamic_keyword]];
                    compiled_content += temp_compiled_content;
                    temp_compiled_content = "";
                    current_find_dynamic_keyword = false;

                    break;
                }
            }
        }

        if(content[content_length] == '(' && find_phar == "true") {
            open_phar_tracer++;
        }

        if(content[content_length] == ')' && find_phar == "true") {
            open_phar_tracer--;
            find_phar = "found";
        }

        if(find_phar == "found") {
            std::string act_phar_keyword = phar_keyword[current_phar_keyword];
            // content_length += act_phar_keyword.length();
            content_length++;
            if(current_find_dynamic_keyword) {
                temp_compiled_content += phar_keyword[current_phar_keyword];
            } else {
                compiled_content += phar_keyword[current_phar_keyword];
            }
            find_phar = "false";
        }


        for(std::size_t index_keyword = 0; index_keyword < keyword.size(); ++index_keyword) { // per keyword e.g. {{, }}, if, else

            int token_length = 0;
            
            // per char keyword e.g. ({, {) -- (}, }) -- i, f -- e, l, s,  e
            for(std::size_t index_char_keyword = 0; index_char_keyword < keyword[index_keyword].size(); ++index_char_keyword) {


                if(keyword[index_keyword][index_char_keyword] == content[content_length + index_char_keyword]){
                    token_length++;
                } else {
                    token_length = 0;
                    break;
                }

            }

            if(token_length > 0) {
                content_length += token_length;
                if(current_find_dynamic_keyword) {
                    temp_compiled_content += act_keyword[index_keyword];
                } else {
                    compiled_content += act_keyword[index_keyword];
                }

                if(phar_keyword.find(keyword[index_keyword]) != phar_keyword.end()) {

                    current_phar_keyword = keyword[index_keyword];
                    find_phar = "true";

                    if (std::find(dynamic_keyword.begin(), dynamic_keyword.end(), keyword[index_keyword]) != dynamic_keyword.end()) {
                        current_find_dynamic_keyword = true;
                    }
                }

                break;
            }   

        }

        if(index_content < content_length) continue;

        content_length++;

        if(current_find_dynamic_keyword) {
            temp_compiled_content += content[index_content];
        } else {
            compiled_content += content[index_content];
        }

        // compiled_content += temp_compiled_content;
    }

    // std::cout << compiled_content << std::endl;
    // std::cout << temp_compiled_content << std::endl;
    compiled_content += temp_compiled_content;
    std::cout << compiled_content << std::endl;

    return 0;
}