#pragma once

#include <phpcpp.h>

#include <fusion/const/construct.cpp>
#include <fusion/components/gate/route/provider/service.h>
#include <fusion/cores/container/container.h>
#include <fusion/regex/route.h>
#include <iostream>


#include <fusion/components/gate/route/method/get.h>
#include <fusion/components/gate/route/method/post.h>


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
};