#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include <database/core.hpp>
#include <regex/wrapper/pcre2.hpp>

namespace serfix {
    class fileio {
        public: std::string static read(std::string filename) {
            Database::set::string({"FUSION_STORE", "FS_ERROR", "Filename"}, filename);
            std::ifstream ifs(filename);
            std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
            return content;
        }

        public: std::string static write(std::string filename, std::string content) {
            regexp::replace("\\/", filename.c_str(), "+", [&](const char *replaced) {
                filename = (std::string)replaced;
            });

            std::string file_id = Php::call("uniqid", "serfix_", true).stringValue()  +"_"+ Database::session_id()+ "_filename_" +filename;
            std::ofstream fileio_cache("../storage/fusion/cache/serfix/" +file_id);
            fileio_cache << content << std::endl;
            fileio_cache.close();

            return file_id;
        }

        public: void static unlink(std::string filename) {
            std::filesystem::remove(filename);
        }
    };
}