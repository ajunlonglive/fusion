#pragma once

#include <phpcpp.h>

#include <views/constra/context.hpp>
#include <regex/wrapper/pcre2.hpp>
#include <database/core.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class Constra : public Php::Base {
    public: std::string render_resource;
    public: std::string starter;
    public: Php::Value variables;
    public: std::string filename;
    public: std::string file_id;

    public: Constra() = default;
    public: virtual ~Constra() = default;

    public: void __construct(Php::Parameters &param) {
        if(Php::count(param) > 2)
            Php::error << "param at least only 2 arguments" << std::flush;
        std::string fname = param[0];

        variables = param[1];
        filename = fname;
    }

    private: void get_file_resource() {
        std::ifstream ifs("../app/Views/templates/" + filename + ".phtml");
        std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
        render_resource = content;
    }

    private: void regist_variable() {
        std::string variable_parse;

        variable_parse += "<?php \n";
        variable_parse += "$variables = json_decode('" + Php::call("json_encode", variables).stringValue() + "', true);\n\n";
       

        for(auto &variable : variables) {
            variable_parse += "$" +(std::string)variable.first+ " = $variables['" +(std::string)variable.first+ "'];\n";
        }

        variable_parse += "?>";

        starter += variable_parse;
    }

    private: void interprete_template() {

        std::string list_pattern;
        // list_pattern += "test\\((.*?)\\)";
        list_pattern += "(?<openphp>\\%php\\s+)|";
        list_pattern += "(?<closephp>\\%ephp)|";

        list_pattern += "(?<openif>\\%if\\s*\\((?<opif>.*?)\\))|";

        // list_pattern += "(?<openif>\\%if)|";
        // list_pattern += "(?<copenif>\\)\\:)|";

        list_pattern += "(?<elif>\\%elif\\s*\\((?<opel>.*?)\\))|";
        list_pattern += "(?<else>\\%else)|";
        list_pattern += "(?<endif>\\%eif)|";

        list_pattern += "(?<variable>\\{\\{(?<var>.*?)\\}\\})|";
        
        list_pattern += "(?<foreach>\\%for\\s*\\((?<arrfor>.*?)as(?<pararr>.*?)\\))|";
        list_pattern += "(?<for>\\%for\\s*\\((?!(.*?)as(.*?))(?<forctx>.*?)\\))|";
        list_pattern += "(?<endfor>\\%efor)";
        // list_pattern += "(?<test>test\\((?<cc>.*?)\\))";

        std::string list_replacement;
        // list_replacement += "test\\($1\\)";
        list_replacement += "${openphp:+ \\<\\?php }";
        list_replacement += "${closephp:+ \\?\\>}";

        list_replacement += "${openif:+\\<\\?php if\\(${opif}\\)\\: \\?\\>}";
        // list_replacement += "${openif:+\\<\\?php if}";
        // list_replacement += "${copenif:+\\)\\: \\?\\>}";

        list_replacement += "${elif:+\\<\\?php elseif\\(${opel}\\)\\: \\?\\>}";
        list_replacement += "${else:+\\<\\?php else\\: \\?\\>}";
        list_replacement += "${endif:+\\<\\?php endif\\; \\?\\>}";

        list_replacement += "${variable:+\\<\\?php echo ${var}; \\?\\>}";

        list_replacement += "${foreach:+\\<\\?php foreach\\(${arrfor} as ${pararr}\\) \\{ \\?\\>}";
        list_replacement += "${for:+\\<\\?php for\\(${forctx}\\) \\{ \\?\\>}";
        list_replacement += "${endfor:+\\<\\?php \\} \\?\\>}";
        
        // list_replacement += "${test:+tost\\(${cc}\\)}";

        regexp::replace(list_pattern.c_str(), render_resource.c_str(), list_replacement.c_str(), [&](const char *replaced) {
            render_resource = (std::string)replaced;
        });
    }

    private: void cache_resource_to_file() {
        file_id = Php::call("uniqid", "constra_", true).stringValue()  +"_"+ Database::session_id()+ ".php";
        std::ofstream constra_cache("../storage/fusion/cache/" +file_id);
        constra_cache << starter << std::endl;
        constra_cache << render_resource << std::endl;
        constra_cache.close();
    }

    public: void __destruct() {
        get_file_resource();

        regist_variable();

        interprete_template();

        cache_resource_to_file();

        Php::require_once("../storage/fusion/cache/" +file_id);

        // std::filesystem::remove("../storage/fusion/cache/" +file_id);
    }
};