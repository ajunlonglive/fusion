#pragma once

#include <phpcpp.h>
#include <iostream>

#pragma once

#include <phpcpp.h>

#include <regex/wrapper/pcre2.hpp>
#include <database/core.hpp>

namespace error {
    namespace internal {
        std::string error_file_filter(std::string filename) {
            const char *result = filename.c_str();
            
            const char *list_pattern = "(?<open>^.*?\\_filename\\_\\.\\.)|(?<closed>\\+)";
            const char *list_replacement = "${open:+}${closed:+\\/}";

            regexp::replace(list_pattern, result, list_replacement, [&](const char *replaced) {
                result = replaced;
            });
            
            std::string app_path = Database::get::string({"FUSION_STORE", "FS_ERROR", "Filename"});
            return app_path + (std::string)result;
        }

        std::string error_message_filter(std::string message) {
            const char * result = message.c_str();

            regexp::match("^Uncaught\\s(ParseError|Error).*?(?=\\sin)", result, [&](const char *matched) {
                result = matched;
            });

            return (std::string)result;
        }

        void fusion_php_error_handler(Php::Parameters &param) {
            Php::Value error = Php::call("error_get_last");
            if (error["type"]) {
                std::string error_html;
                error_html += "<script>";
                error_html += "document.onreadystatechange = function () {";
                error_html += "if (document.readyState == \"interactive\") {";
                error_html += "document.querySelector(\"*\").innerHTML = `";
                error_html += "<!DOCTYPE html><style>*{background: #ffffff; color: #000000; font-size: 18px;}#fusion-error{border: 4px solid grey; margin: 10px; padding: 10px;}.error-type{font-weight: bold;}</style><div id='fusion-error'> <div id='top'> <span class='error-type'>InternalPhpError:</span> <span class='error-message'>" +error_message_filter((std::string)error["message"])+ "</span><br /><span class='error-line'>at line <b>" +(std::string)error["line"]+ "</b></span><br /> <span class='error-line'>in <b>" +error_file_filter((std::string)error["file"])+ "</b></span> </div>";
                error_html += "`;";
                error_html += "}}";
                error_html += "</script>";

                Php::out << error_html << std::flush;
            }
        }
    }
}