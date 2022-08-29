#pragma once

#include <phpcpp.h>

#include <http/request/request.hpp>
#include <cores/container/default.hpp>

#include <iostream>
#include <vector>


namespace cores {   


class c_container : public Php::Base {
    
   /**
     * @note Fusion import the default class all lib injection
     *       which is stored in ./default.h
     * 
     *      ** The default class all from fusion enviroment, which auto included when user type-hint in parameter.
     */
    private: Php::Object static m_get_dependency(std::string type_name) {
        cores::container::c_default_dependency default_container;
        return default_container.m_dependencies_context(type_name);
    }

    /** 
     * @brief the "Method" method used for Reflection each class-method to get parameter type & interface as list.
     * 
     * @param cclass        (std::string) A param for class name target
     * @param mmethod       (std::stirng) A param for method name target
     * 
     * @return              (std::vector<Php::Object>) return a vector data with (Php::Object) type. each element contains a object method for injection requirements
     * 
     */
    public: std::vector<Php::Value> static m_method(std::string class_name, std::string method_name) {
        // Php::Value dependencies = Php::eval("$ps = (new ReflectionMethod('" +class_name+ "', '" +method_name+ "'))->getParameters(); $dp = []; foreach($ps as $p) { $dp[(string) $p->getName()] = (string) $p->getType();}return $dp;").mapValue();
        Php::Value reflect_function = Php::Object("ReflectionMethod", class_name, method_name);
        Php::Value get_param = reflect_function.call("GetParameters").mapValue();

        // Create map for pushed type name
        std::vector<Php::Value> depen_group;
        // Iterate all type for casting and pushing to dependencies group
        for(auto &p : get_param) {
            // Deprecated in PHP 7.1-7.4~ for ReflectionType::__toString(); if direct cast **->getType to string
            // Php::Value get_type = (p.second).call("getType");
            // depen_group.push_back(m_get_dependency( (std::string)get_type));

            // Alternative, must call the getName for getType to casting name to string value
            Php::Value get_type = (p.second).call("getType");
            Php::Value get_type_name = get_type.call("getName");
            
            // Push the type to dependencies group map
            depen_group.push_back(m_get_dependency( (std::string)get_type_name));
        }

        // Return the dependencies group
        return depen_group;
    }

    /**
     * @brief the "Function" method used for Reflection each function to get parameter type & interface as list.
     * 
     * 
     * @return (std::vector<Php::Object>) return a vector data with (Php::Object) type. each element contains a object method for injection requirements
     * 
     */
    public: std::vector<Php::Value> static m_function(Php::Value function_name) {
        // Php::Value dependencies = Php::eval("$ps = (new ReflectionFunction('" +function_name+ "'))->getParameters(); $dp = []; foreach($ps as $p) { $dp[(string) $p->getName()] = (string) $p->getType();}return $dp;").mapValue();

        Php::Value reflect_function = Php::Object("ReflectionFunction", function_name);
        Php::Value get_param = reflect_function.call("GetParameters").mapValue();

        std::vector<Php::Value> depen_group;
        for(auto &p : get_param) {
            // Deprecated in PHP 7.1-7.4~ for ReflectionType::__toString(); if direct cast **->getType to string
            // // Php::Value get_type = (p.second).call("getType");
            // // depen_group.push_back(default_list( (std::string)get_type));

                // Alternative, must call the getName for getType to casting name to string value
            Php::Value get_type = (p.second).call("getType");
            Php::Value get_type_name = get_type.call("getName");

            // Push the type to dependencies group map
            depen_group.push_back(m_get_dependency( (std::string)get_type_name));
        }

        return depen_group;
    }
};


}