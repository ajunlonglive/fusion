#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/cores/autoload/loader.h>
#include <fusion/controllers/route/service.cpp>

class Destruct : public Php::Base {
    /**
     * @brief As router initiliazed, default action for filter double route uri.
     *        Run first router initiliazed for capture double route uri, same data for validator later
     *        if same route uri was found, Fusion will thrown error and stop the code execute for else it will continue
     */
    public: void static route_init() {
        loader::route(); // run first router initiliazed
        Database::set::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"}, false); // if not found, reset data
        RouteService::web::reset_route_list(); // reset web route list
        loader::route(); // run again for first router initiliazed
    }
};