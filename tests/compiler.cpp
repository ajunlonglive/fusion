#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>


int main() {
    
    std::ifstream ifs("file.php");
    std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
    // std::cout << content[0] << std::endl;
    std::vector<std::string> keyword = {
        "%php ",
        " %ephp",

        "{{",
        "}}",

        "%if ", 
        "%else ",
        "%eif ",

        "%for ",
        "%efor ",
    };
    std::vector<std::string> act_keyword = {
        "<?php ",
        " ?>",

        "<?php echo ",
        " ?>",
        "<?php if ",
        "<?php else: ?>",
        "<?php endif; ?>",

        "<?php for ",
        "<?php } ?>",
    };
    std::unordered_map<std::string, std::string> phar_keyword;
                            phar_keyword["%if"] = "): ?>";
                            phar_keyword["%for"] = ") { ?>";
                            

    int content_length = 0;
    std::string compiled_content = "";

    int open_phar_tracer = 0;
    std::string current_phar_keyword = "";

    std::string find_phar = "false";

    int looped_count = 0;

    for(std::size_t index_content = 0; index_content < content.size(); ++index_content) {
        if(index_content < content_length) continue;

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
            compiled_content += phar_keyword[current_phar_keyword];
            find_phar = "false";
        }


        for(std::size_t index_keyword = 0; index_keyword < keyword.size(); ++index_keyword) { // per keyword e.g. {{, }}, if, else

            int token_length = 0;

            // per char keyword e.g. {, { -- }, } -- i, f -- e, l, s,  e
            for(std::size_t index_char_keyword = 0; index_char_keyword < keyword[index_keyword].size(); ++index_char_keyword) {
                // std::cout << keyword[index_keyword][index_char_keyword] << " == " << content[content_length + index_char_keyword] << std::endl;

                if(keyword[index_keyword][index_char_keyword] == content[content_length + index_char_keyword]){
                    token_length++;

                    std::cout << "len token : " << token_length << std::endl;
                } else {
                    token_length = 0;
                    break;
                }
            }

            if(token_length > 0) {
                content_length += token_length;
                // std::cout << "keyword keganti : \"" << act_keyword[index_keyword] << "\" -- " << index_keyword << std::endl;
                compiled_content += act_keyword[index_keyword];

                if(phar_keyword.find(keyword[index_keyword]) != phar_keyword.end()) {
                    current_phar_keyword = keyword[index_keyword];
                    find_phar = "true";
                }

                break;
            }   

            // looped_count++;
            // std::cout << "IS LOOPED : " << looped_count << std::endl;
        }

        if(index_content < content_length) continue;
        content_length++;
        compiled_content += content[index_content];
    }

    std::cout << compiled_content << std::endl;

    return 0;
}