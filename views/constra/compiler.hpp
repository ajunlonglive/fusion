#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

std::string compile(std::string content) {
    

   content += " ";

    /**
     * @brief Using lexicar analysis for parsing code, but more simple
     * 
     */
    // Reserved keyword for Constra compiler
    std::vector<std::string> keyword = {
        "%php ",            // <?php\s
        "%php\n",            // <?php\s
        " php%",           // ?>\s
        "\nphp%",           // ?>\s

        "{{",               // <?php echo
        "}}",               // ?>


        "%if(",              // <?php if(...): ?> \s
        "%if ",              // <?php if(...): ?> \s
        "%if\n",              // <?php if(...): ?> \s
        "%else%",            // <?php else: ?> \s
        " if%",             // <?php endif; ?> \s
        "\nif%",             // <?php endif; ?> \s

        "%for(",             // <?php for(...) { ?>
        "%for ",             // <?php for(...) { ?>
        "%for\n",             // <?php for(...) { ?>
        " for%",            // } ?>
        "\nfor%",            // } ?>

        // For minimum condintion bracing phar
        "|",
    };
    
    // Reserved keyword for PHP engine
    std::vector<std::string> act_keyword = {
        "<?php ",           // %php
        "<?php\n",           // %php
        " ?>",              // %ephp
        "\n?>",              // %ephp

        "<?php echo(",      // {{
        ")?>",              // }}

        "<?php if(",         // %if
        "<?php if ",         // %if
        "<?php if\n",         // %if
        "<?php else: ?>",   // %else
        " <?php endif; ?>",  // %eif
        "\n<?php endif; ?>",  // %eif

        "<?php for(",        // %for
        "<?php for ",        // %for
        "<?php for\n",        // %for
        " <?php } ?>",       // %efor
        "\n<?php } ?>",       // %efor

        // For minimum condintion bracing phar
        ", ",
    };

    // std::unordered_map<std::string, std::string> test;
    //     test["|"] = ",";


    std::vector<std::string> open_minim_cond_phar = {"{{"};

    std::vector<std::string> close_minim_cond_phar = {"}}"};
        
    std::vector<std::string> minim_cond_phar_keyword = {"|"};
        
    /**
     * @brief   Use for find actual closed phar, a keyword with phar closure.
     *          Heap the compiled content to anonther reserverd memory until followed closed phar for each keyword.
     * 
     */
    std::unordered_map<std::string, std::string> phar_keyword;
        phar_keyword["%if("] = "): ?>";      // if ...followed until... (() ()) <- ): ?> -> last brace;
        phar_keyword["%if "] = "): ?>";      // if ...followed until... (() ()) <- ): ?> -> last brace;
        phar_keyword["%if\n"] = "): ?>";      // if ...followed until... (() ()) <- ): ?> -> last brace;

        phar_keyword["%for("] = ") { ?>";    // for ...followed until... (() ()) <- } ?> -> last brace;
        phar_keyword["%for "] = ") { ?>";    // for ...followed until... (() ()) <- } ?> -> last brace;
        phar_keyword["%for\n"] = ") { ?>";    // for ...followed until... (() ()) <- } ?> -> last brace;


    std::vector<std::string> non_whitespace_open_phar_keyword = {
        "%if(",
        "%for(",
    };

    std::vector<std::string> non_whitespace_dynamic_open_phar_keyword = {
        "%for(",
    };

    /**
     * @brief Dynamic keyword used for multi keyword (prefix-parenthess) assigned to related sub-keyword.
     *        The simple example when user using for and foreach, the different is when
     *        foreach will used, the type-hints " as " will come, and then make assigned
     *        to " as " sub-keyword.
     *        e.g. for( ... )  "without sub-keyword ' as ' "
     *        e.g. foreach( ... as ...) "used ' as ' sub-keyword"
     * 
     */
    std::vector<std::string> dynamic_keyword = {"%for"};
    std::vector<std::string> token_dynamic_keyword = {" as "};
    std::unordered_map<std::string, std::string> pattern_dynamic_keyword;
                            pattern_dynamic_keyword[" as "] = "each";


    // Used for push a char as final result
    std::string compiled_content = "";
    // Used for temporare stack as merge to compiled content after closed dynamic phar
    std::string temp_compiled_content = "";

    // Used for address index result, different with index from actual source code
    int content_length = 0;
    // Parameter to count last trace open to close phar
    int open_phar_tracer = 0;
    // Used for param to checking up current phar keyword
    std::string current_phar_keyword = "";

    bool current_minim_cond_phar = false;

    // Used for finding phar relation, the variable had 3 value as std::string
    // "false", "found", "true"
    std::string find_phar = "false";

    // Used for param to check current condition if compiler finding dynamic keyword
    bool current_find_dynamic_keyword = false;

    for(std::size_t index_content = 0; index_content < content.size(); ++index_content) {

        if(index_content < (size_t)content_length) continue;

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
            
            if(open_phar_tracer == 0)
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

                if(!current_minim_cond_phar &&  std::find(minim_cond_phar_keyword.begin(), minim_cond_phar_keyword.end(), keyword[index_keyword]) != minim_cond_phar_keyword.end()) {
                     if(current_find_dynamic_keyword) {
                        temp_compiled_content += keyword[index_keyword];
                    } else {
                        compiled_content += keyword[index_keyword];
                    }

                    break;
                }

                if(current_find_dynamic_keyword) {
                    temp_compiled_content += act_keyword[index_keyword];
                } else {
                    compiled_content += act_keyword[index_keyword];
                }

                
                if (std::find(open_minim_cond_phar.begin(), open_minim_cond_phar.end(), keyword[index_keyword]) != open_minim_cond_phar.end()) {
                    current_minim_cond_phar = true;
                }

                if(std::find(close_minim_cond_phar.begin(), close_minim_cond_phar.end(), keyword[index_keyword]) != close_minim_cond_phar.end()) {
                    current_minim_cond_phar = false;
                }

                // Find key exists

                if(phar_keyword.find(keyword[index_keyword]) != phar_keyword.end()) {

                    current_phar_keyword = keyword[index_keyword];

                    find_phar = "true";

                    // Vector if exists
                    if(std::find(non_whitespace_open_phar_keyword.begin(), non_whitespace_open_phar_keyword.end(), current_phar_keyword) 
                                    != non_whitespace_open_phar_keyword.end()) {
                        open_phar_tracer++;
                        
                        if(std::find(non_whitespace_dynamic_open_phar_keyword.begin(), non_whitespace_dynamic_open_phar_keyword.end(), current_phar_keyword) 
                            != non_whitespace_dynamic_open_phar_keyword.end()) {
                                temp_compiled_content += "(";
                        }
                    }


                    // std::cout << keyword[index_keyword] << std::endl;
                    // Vector if exists
                    if (std::find(dynamic_keyword.begin(), dynamic_keyword.end(), keyword[index_keyword].substr(0, keyword[index_keyword].size() - 1)) != dynamic_keyword.end()) {
                    // if (std::find(dynamic_keyword.begin(), dynamic_keyword.end(), keyword[index_keyword]) != dynamic_keyword.end()) {
                        std::cout << "oke ada" << std::endl;
                        compiled_content.pop_back();
                        current_find_dynamic_keyword = true;
                    }
                }

                break;
            }   

        }

        if(index_content < (size_t)content_length) continue;

        content_length++;

        if(current_find_dynamic_keyword) {
            temp_compiled_content += content[index_content];
        } else {
            compiled_content += content[index_content];
        }

    }

    compiled_content += temp_compiled_content;

    return compiled_content;
}