#pragma once

#include <phpcpp.h>
#include <iostream>

#pragma once

#include <phpcpp.h>

#include <regex/wrapper/pcre2.hpp>

namespace error {
    namespace internal {
        void fusion_php_error_handler(Php::Parameters &param) {
            Php::Value error = Php::call("error_get_last");
            if (error["type"]) {
                std::string error_html;
                error_html += "<script src=\"https://code.jquery.com/jquery-3.6.1.min.js\"></script>";
                error_html += "<script>";
                error_html += "$(document).ready(function() {";
                error_html += "$.when($(\"*:not(.fusion-error)\")).then(function() {";
                error_html += "$(\"*\").html(`";

                error_html += "<!DOCTYPE html><style>*{background: #ffffff; color: #000000; font-size: 18px;}#fusion-error{border: 4px solid grey; margin: 10px; padding: 10px;}.error-type{font-weight: bold;}</style><div id='fusion-error'> <div id='top'> <span class='error-type'>InternalPhpError:</span> <span class='error-message'>" +(std::string)error["message"]+ "</span><br /><span class='error-line'>at line <b>" +(std::string)error["line"]+ "</b></span><br /> <span class='error-line'>in <b>" +(std::string)error["file"]+ "</b></span> </div>";

                error_html += "`);";
                error_html += "});";
                error_html += "});";
                error_html += "</script>";

                Php::out << error_html << std::flush;
            }
        }
    }
}