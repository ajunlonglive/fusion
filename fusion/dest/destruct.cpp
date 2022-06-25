#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/cores/autoload/loader.h>
#include <fusion/controllers/route/service.cpp>

class Destruct : public Php::Base {
    public: void static route_init() {
        loader::route();
        Database::set::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"}, false);
        RouteService::web::reset_route_list();
        loader::route();
    }
};