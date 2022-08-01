#pragma once

#include <phpcpp.h>

#include <fusion/const/construct.hpp>
#include <fusion/components/gate/route/provider/service.hpp>
#include <fusion/cores/container/container.hpp>
#include <fusion/regex/route.hpp>
#include <iostream>


#include <fusion/components/gate/route/method/get.hpp>
#include <fusion/components/gate/route/method/post.hpp>
#include <fusion/components/gate/route/method/put.hpp>
#include <fusion/components/gate/route/method/patch.hpp>
#include <fusion/components/gate/route/method/delete.hpp>


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
};