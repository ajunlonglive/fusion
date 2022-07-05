#pragma once

#include <phpcpp.h>

#include <fusion/views/constra/context.h>
#include <fusion/regex/wrapper/pcre2.cpp>

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include <fusion/database/core.cpp>

class Constra : public Php::Base {
    public: std::string render_resource;
    public: std::string filename;
    public: std::string file_id;

    public: Constra() = default;
    public: virtual ~Constra() = default;

    public: void __construct(Php::Parameters &param) {
        std::string fname = param[0];
        filename = fname;
    }

    private: void get_file_resource() {
        std::ifstream ifs("../app/Views/templates/" + filename + ".phtml");
        std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
        render_resource = content;
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
        list_replacement += "${endif:+<\\?php endif\\; \\?\\>}";
        // list_replacement += "${test:+tost\\(${cc}\\)}";

        regexp::replace(list_pattern.c_str(), render_resource.c_str(), list_replacement.c_str(), [&](const char *replaced) {
            render_resource = (std::string)replaced;
        });
    }

    private: void cache_resource_to_file() {
        file_id = Php::call("uniqid", "constra_", true).stringValue()  +"_"+ Database::session_id()+ ".php";
        std::ofstream constra_cache("../storage/fusion/cache/" +file_id);
        constra_cache << render_resource << std::endl;
        constra_cache.close();
    }

    public: void __destruct() {
        get_file_resource();

        interprete_template();

        cache_resource_to_file();

        Php::require_once("../storage/fusion/cache/" +file_id);

        // std::filesystem::remove("../storage/fusion/cache/" +file_id);
    }
};