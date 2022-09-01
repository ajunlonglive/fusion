
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>


int main() {

    std::ifstream ifs("serfix.php");
    std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );

    content = " " + content;
    std::string compiled_content = "";
    bool is_open_phar_state = false;

    std::vector<std::string> keyword = {
        "echos ",
        "echos\n",
    };

    std::vector<std::string> act_keyword = {
        "echos ",
        "echos\n",
    };

    std::vector<std::string> prefix_keyword = {
        "\n",
        " ",
        "}",
        ")",
        ";",
    };

    

    std::unordered_map<std::string, std::string> close_phar;
        close_phar[";"] = ");";

    
    int content_length = 0;
    bool is_prefix_key = false;

    for(std::size_t index_content = 0; index_content < content.size(); ++index_content) {
        if(index_content < (size_t)content_length) continue;
        
        std::string tmp_index_content(1, content[index_content]);
        if(is_open_phar_state && close_phar.find(tmp_index_content) != close_phar.end()) {
            compiled_content += close_phar[tmp_index_content];
            content_length++;
            is_open_phar_state = false;
        }
        
        for(std::size_t index_keyword = 0; index_keyword < keyword.size(); ++index_keyword) {
            int token_length = 0;

            for(std::size_t index_char_keyword = 0; index_char_keyword < keyword[index_keyword].size(); ++index_char_keyword) {


                if(!is_prefix_key && std::find(prefix_keyword.begin(), prefix_keyword.end(), tmp_index_content) != prefix_keyword.end()) {
                    std::cout << tmp_index_content << std::endl;
                    is_prefix_key = true;
                }

                if(is_prefix_key && keyword[index_keyword][index_char_keyword] == content[index_content + index_char_keyword]) {
                    // std::cout << "ada juga bos" << std::endl;
                    token_length++;
                } else {
                    token_length = 0;
                    break;
                }
            }

            if(token_length > 0) {
                is_open_phar_state = true;
                content_length += token_length;
                compiled_content += act_keyword[index_keyword] + "(";
                is_prefix_key = false;
                break;
            }
            
        }


        // std::cout << index_content << " : " << content_length << std::endl;
        if(index_content < (size_t)content_length) continue;

        content_length++;
        compiled_content += content[index_content];

    }

    std::cout << compiled_content << std::endl;
    return 0;
}