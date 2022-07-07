#pragma once

#include <phpcpp.h>

#include <fusion/http/request/request.cpp>

#include <iostream>
#include <vector>

class Container : public Php::Base {
    private: Php::Object static default_list(std::string type_name) {
        std::map <std::string, Php::Object> dependencies_list;

        Request *request = new Request;
        dependencies_list["Fusion\\Http\\Request"] = Php::Object("Fusion\\Http\\Request", request);
        
        // Php::Object res = dependencies_list[type_name]; 
        return dependencies_list[type_name];
    }

    public: std::vector<Php::Object> static loader(std::string cclass, std::string mmethod) {
        Php::Value dependencies = Php::eval("$ps = (new ReflectionMethod('" +cclass+ "', '" +mmethod+ "'))->getParameters(); $dp = []; foreach($ps as $p) { $dp[(string) $p->getName()] = (string) $p->getType();}return $dp;").mapValue();
        std::vector<Php::Object> depen_group;
        for(auto &param : dependencies) {
            depen_group.push_back(default_list(param.second));
            // Php::out << param.first << " = " << param.second << "<br />" << std::flush;
        }

        return depen_group;
    }
};