#pragma once

#include <phpcpp.h>

#include <fusion/http/request/request.cpp>
#include <fusion/cores/container/default.h>

#include <iostream>
#include <vector>

class Container : public Php::Base {

    /**
     * @brief A method used for return object a selected dependencies for each type
     * 
     * @param type_name (std::string) used for selecting type class name based string name class
     * 
     * @return (Pho::Object) A Object based for PHP Context, returned current context dependencies. 
     * 
     */
    private: Php::Object static default_list(std::string type_name) {
        /**
         * @note Fusion import the default class all lib injection
         *       which is stored in ./default.h
         * 
         *      ** The default class all from fusion enviroment, which auto included when user type-hint in parameter.
         */
        DefaultContainer default_container;
        return default_container.object_class(type_name);
    }

   /**
     * @brief the "loader" method used for Reflection each class-method to get parameter type & interface as list.
     * 
     * @param cclass        (std::string) A param for class name target
     * @param mmethod       (std::stirng) A param for method name target
     * 
     * @return              (std::vector<Php::Object>) return a vector data with (Php::Object) type. each element contains a object method for injection requirements
     * 
     */
    public: std::vector<Php::Value> static loader(std::string cclass, std::string mmethod) {
        Php::Value dependencies = Php::eval("$ps = (new ReflectionMethod('" +cclass+ "', '" +mmethod+ "'))->getParameters(); $dp = []; foreach($ps as $p) { $dp[(string) $p->getName()] = (string) $p->getType();}return $dp;").mapValue();

        // for(auto &name_of : dependencies) { 
        //     Php::out << name_of.first << " : " << name_of.second << "<br />" << std::flush;
        // }

        std::vector<Php::Value> depen_group;
        for(auto &param : dependencies) {
            depen_group.push_back(default_list(param.second));
        }

        return depen_group;
    }
};