#pragma once

#include <phpcpp.h>

#include <utils/string.hpp>

namespace RequestUtils {
    Php::Value uri_route_split(std::string uri_route, bool state = false) {
        
        /**
         * use conditionals for only slash routing
         * if uri_route only a "/" capture and use second conditional
         * if state is given false return 0;
         * if state is give true return a piece of array given only "/" as elements.
         */

        if(uri_route == "/") {
            if(state) 
                return 0;
            else
                return {"/"};
        }

        /**
         * remove first slash and last slash in routing uri
         * e.g. /user/:id/../../ = user/:id/../..
         */

        uri_route = uri_route.substr(1, uri_route.length() - 2);
        

        // replaceAll(uri_route, "$fs_bs$", "\\");

        /**
         * split uri_route as splitted by delim "/"
         * e.g. /user/:id/.. = ["user", ":id"]
         */

        std::vector<std::string> uri_route_split = utils::str_split("/", uri_route);

        /**
         * return context from what second argumen
         * when second argumen is:
         * false : return uri_route as array of splitted by delim "/"
         * true  : return uri_route length/size
         */

        if(state) 
            return (int)uri_route_split.size();
        else
            return uri_route_split;
    }

}