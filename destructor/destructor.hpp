#pragma once

#include <phpcpp.h>
#include <database/core.hpp>
#include <database/redis.hpp>
#include <cores/autoload/loader.hpp>
#include <components/gate/route/provider/service.hpp>
#include <components/gate/route/provider/smart.hpp>
#include <destructor/destructor.hpp>

class Destruct : public Php::Base {
    /**
     * @brief As router initiliazed, default action for filter double route uri.
     *        Run first router initiliazed for capture double route uri, same data for validator later
     *        if same route uri was found, Fusion will thrown error and stop the code execute for else it will continue
     */
    public: void static route_init() {

        // running first loader::route, grab all php files which include router config and aneccesary
        loader::route();
        
        // run all service in SmartRouter
        SmartRouter::run();

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
        RouteService::web::reset_route_list(); // reset web route list
        SmartRouter::permist_step_mode();

        // run again for trigger a routing grouping
        loader::route();
        RouteService::web::flush();

        // RedisDb::flushall();
    }

    public: void static internal_error_handler() {
        // When Serfix used for pre-parser to CGI, add data in dbcore to get actual script for error events
        Database::set::string({"FUSION_STORE", "FS_ERROR", "Filename"}, "");

        // Get data for error handler use to
        std::string php_error_handler = Database::get::string({"FUSION_STORE", "FS_ERROR", "Php_Error_Handler_Function"});
        
        // Set register shutdown for function PhpErrorHandler, to catch all error events
        Php::call("register_shutdown_function", php_error_handler);
    }

    public: void static session_reset() {
        Php::call("session_destroy");
    }
};