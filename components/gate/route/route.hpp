#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <services/route/guard.hpp>
#include <cores/container/container.hpp>
#include <regex/route.hpp>
#include <iostream>


#include <components/gate/route/method/get.hpp>
#include <components/gate/route/method/post.hpp>
#include <components/gate/route/method/head.hpp>
#include <components/gate/route/method/put.hpp>
#include <components/gate/route/method/patch.hpp>
#include <components/gate/route/method/options.hpp>
#include <components/gate/route/method/redirect.hpp>
#include <components/gate/route/method/any.hpp>
#include <components/gate/route/method/method.hpp>

namespace components {
    namespace gate {



class c_route : public Php::Base {
    public: c_route() {
        // A Guard check if user really mean it for using Fusion framewok
        // When true (mean used it) is return nothing and non-blocking
        // But if false, is return internal PHP error exception and blocking
        constructor::c_run::m_framework();
    }

    // Return singleton context (a declared object) when user use "get" method
    public: Php::Value static m_get(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_get *route_get = new components::gate::route::method::c_route_get(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Get", route_get);
    }

    // Return singleton context (a declared object) when user use "post" method
    public: Php::Value static m_post(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_post *route_post = new components::gate::route::method::c_route_post(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Post", route_post);
    }
  
    // Return singleton context (a declared object) when user use "head" method
    public: Php::Value static m_head(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_head *route_head = new components::gate::route::method::c_route_head(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Head", route_head);
    }

    // Return singleton context (a declared object) when user use "put" method
    public: Php::Value static m_put(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_put *route_put = new components::gate::route::method::c_route_put(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Put", route_put);
    }


    // Return singleton context (a declared object) when user use "patch" method
    public: Php::Value static m_patch(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_patch *route_patch = new components::gate::route::method::c_route_patch(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Patch", route_patch);
    }

    // Return singleton context (a declared object) when user use "options" method
    public: Php::Value static m_options(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_options *route_options = new components::gate::route::method::c_route_options(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Options", route_options);
    }
    
    // Return singleton context (a declared object) when user use "redirect" method
    public: Php::Value static m_redirect(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_redirect *route_redirect = new components::gate::route::method::c_route_redirect(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Redirect", route_redirect);
    }

    // Return singleton context (a declared object) when user use "any" method
    public: Php::Value static m_any(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_any *route_any = new components::gate::route::method::c_route_any(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Any", route_any);
    }

    // Return singleton context (a declared object) when user use "method" method
    public: Php::Value static m_method(Php::Parameters &param) {
        c_route __construct;

        components::gate::route::method::c_route_method *route_method = new components::gate::route::method::c_route_method(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Method", route_method);
    }
};


    }
}