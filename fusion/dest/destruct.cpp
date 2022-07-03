#pragma once

#include <phpcpp.h>
#include <fusion/database/core.cpp>
#include <fusion/cores/autoload/loader.h>
#include <fusion/controllers/route/service.cpp>
#include <fusion/controllers/route/smart.h>
#include <fusion/dest/destruct.cpp>

class Destruct : public Php::Base {
    /**
     * @brief As router initiliazed, default action for filter double route uri.
     *        Run first router initiliazed for capture double route uri, same data for validator later
     *        if same route uri was found, Fusion will thrown error and stop the code execute for else it will continue
     */
    public: void static route_init() {
        // running first loader::route, grab all php files which include router config
        loader::route();
        
        // if router can't find any double/twice router grouping, reset data parameter
        SmartRouter::reset_v_double();

        /**
         * @brief Running second procedural for security purpose,
         *        for yet, it will run SmartRouter procedures. So for the first, clean the router_list in $_SESSION.
         *        second, run again loader::router() for trigger routering grouping
         *        and last, capture all grouping state after reset_v_double(), and run SmartRouter::run()
         */

        // for peformance matters, actually we can throw state for debug purpose or production.
        // if (debug_only == ok?) run the code...

        // reset FS_Web_Route_list again for running procedure again
        RouteService::web::reset_route_list(); // reset web route list

        // run again for trigger a routing grouping
        loader::route(); 

        // run all service in SmartRouter
        SmartRouter::run();
    }

    public: void static session_reset() {
        Php::call("session_destroy");
    }
};