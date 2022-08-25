#pragma once

#include <phpcpp.h>

#include <constructor/constructor.hpp>
#include <components/gate/route/provider/service.hpp>
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


class Route : public Php::Base {
    public: Route() {
        // A Guard check if user really mean it for using Fusion framewok
        // When true (mean used it) is return nothing and non-blocking
        // But if false, is return internal PHP error exception and blocking
        Construct::framework();
    }

    // Return singleton context (a declared object) when user use "get" method
    public: Php::Value static get(Php::Parameters &param) {
        Route __construct;

        RouteGet *route_get = new RouteGet(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Get", route_get);
    }

    // Return singleton context (a declared object) when user use "post" method
    public: Php::Value static post(Php::Parameters &param) {
        Route __construct;

        RoutePost *route_post = new RoutePost(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Post", route_post);
    }
  
    // Return singleton context (a declared object) when user use "head" method
    public: Php::Value static head(Php::Parameters &param) {
        Route __construct;

        RouteHead *route_head = new RouteHead(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Head", route_head);
    }

    // Return singleton context (a declared object) when user use "put" method
    public: Php::Value static put(Php::Parameters &param) {
        Route __construct;

        RoutePut *route_put = new RoutePut(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Put", route_put);
    }


    // Return singleton context (a declared object) when user use "patch" method
    public: Php::Value static patch(Php::Parameters &param) {
        Route __construct;

        RoutePatch *route_patch = new RoutePatch(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Patch", route_patch);
    }

    // Return singleton context (a declared object) when user use "options" method
    public: Php::Value static options(Php::Parameters &param) {
        Route __construct;

        RouteOptions *route_options = new RouteOptions(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Options", route_options);
    }
    
    // Return singleton context (a declared object) when user use "redirect" method
    public: Php::Value static redirect(Php::Parameters &param) {
        Route __construct;

        RouteRedirect *route_redirect = new RouteRedirect(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Redirect", route_redirect);
    }

    // Return singleton context (a declared object) when user use "any" method
    public: Php::Value static any(Php::Parameters &param) {
        Route __construct;

        RouteAny *route_any = new RouteAny(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Any", route_any);
    }

    // Return singleton context (a declared object) when user use "method" method
    public: Php::Value static method(Php::Parameters &param) {
        Route __construct;

        RouteMethod *route_method = new RouteMethod(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Method", route_method);
    }
};