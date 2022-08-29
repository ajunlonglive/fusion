#pragma once

#include <phpcpp.h>
#include <transport/session/session.hpp>
// #include <database/redis.hpp>
#include <cores/autoload/loader.hpp>
#include <services/route/route.hpp>
#include <services/route/guard.hpp>
#include <destructor/destructor.hpp>

#include <fstream>
#include <filesystem>

namespace destructor {


class c_run : public Php::Base {
    /**
     * @brief As router initiliazed, default action for filter double route uri.
     *        Run first router initiliazed for capture double route uri, same data for validator later
     *        if same route uri was found, Fusion will thrown error and stop the code execute for else it will continue
     */
    public: void static m_route_init() {

        // running first loader::route, grab all php files which include router config and aneccesary
        cores::autoload::c_loader::m_route();
        
        // run all service in SmartRouter
        services::route::c_guard::m_run();

        // if router can't find any double/twice router grouping, reset data parameter
        // SmartRouter::reset_v_double();

        /**
         * @brief Running second procedural for security purpose,
         *        for yet, it will run SmartRouter procedures. So for the first, clean the router_list in $_SESSION.
         *        second, run again loader::router() for trigger routering grouping
         *        and last, capture all grouping state after reset_v_double(), and run SmartRouter::run()
         */

        // for peformance matters, actually we can throw state for debug purpose or production.
        // if (debug_only == ok?) run the code...

        // reset FS_Web_Route_list again for running procedure again
        services::route::c_web::m_reset_route_list(); // reset web route list
        services::route::c_guard::m_permist_step_mode();

        // run again for trigger a routing grouping
        cores::autoload::c_loader::m_route();

        services::route::c_web::m_flush();

        // RedisDb::flushall();
    }

    public: void static m_session_reset() {
        Php::call("session_destroy");
    }
};


}