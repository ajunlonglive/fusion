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
#include <components/gate/route/method/delete.hpp>
#include <components/gate/route/method/options.hpp>
#include <components/gate/route/method/redirect.hpp>
#include <components/gate/route/method/any.hpp>
#include <components/gate/route/method/method.hpp>


class Route : public Php::Base {
    public: Route() {
        Construct::framework();

        
    }

    public: Php::Value static Get(Php::Parameters &param) {
        Route __construct;

        RouteGet *routeget = new RouteGet(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Get", routeget);
    }

    public: Php::Value static Post(Php::Parameters &param) {
        Route __construct;

        RoutePost *routepost = new RoutePost(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Post", routepost);
    }
  
    public: Php::Value static Head(Php::Parameters &param) {
        Route __construct;

        RouteHead *routehead = new RouteHead(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Head", routehead);
    }

    public: Php::Value static Put(Php::Parameters &param) {
        Route __construct;

        RoutePut *routeput = new RoutePut(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Put", routeput);
    }

    public: Php::Value static Patch(Php::Parameters &param) {
        Route __construct;

        RoutePatch *routepatch = new RoutePatch(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Patch", routepatch);
    }

    public: Php::Value static Delete(Php::Parameters &param) {
        Route __construct;

        RouteDelete *routedelete = new RouteDelete(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Delete", routedelete);
    }
     
    public: Php::Value static Options(Php::Parameters &param) {
        Route __construct;

        RouteOptions *routeoptions = new RouteOptions(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Options", routeoptions);
    }
    
    public: Php::Value static Redirect(Php::Parameters &param) {
        Route __construct;

        RouteRedirect *routeredirect = new RouteRedirect(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Delete", routeredirect);
    }

    public: Php::Value static Any(Php::Parameters &param) {
        Route __construct;

        RouteAny *routeany = new RouteAny(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Any", routeany);
    }

    public: Php::Value static Method(Php::Parameters &param) {
        Route __construct;

        RouteMethod *routemethod = new RouteMethod(param);
        return Php::Object("Fusion\\Components\\Gate\\Route\\Method\\Method", routemethod);
    }
};