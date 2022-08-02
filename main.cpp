#include <includes.h>

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("fusion", "1.0");

        Php::Namespace fusion("Fusion");

        Php::Class<Engine>          engine("Cores\\Engine");
        Php::Class<Autoload>        autoload("Cores\\Autoload");
        Php::Class<Route>           route("Components\\Gate\\Route");
        Php::Class<RouteContext>    routecontext("Components\\Gate\\Route\\Context");
        Php::Class<Controller>      controller("Controllers\\Controller");
        
        Php::Class<Request>         request("Http\\Request");
        Php::Class<RouteGet>        routeget("Components\\Gate\\Route\\Method\\Get");
        Php::Class<RoutePost>       routepost("Components\\Gate\\Route\\Method\\Post");
        Php::Class<RoutePut>        routeput("Components\\Gate\\Route\\Method\\Put");
        Php::Class<RoutePatch>      routepatch("Components\\Gate\\Route\\Method\\Patch");
        Php::Class<RouteDelete>     routedelete("Components\\Gate\\Route\\Method\\Delete");
        Php::Class<RouteRedirect>   routeredirect("Components\\Gate\\Route\\Method\\Redirect");
        Php::Class<RouteAny>        routeany("Components\\Gate\\Route\\Method\\Any");

        Php::Class<Constra>         constra("Views\\Constra");
        
        constra.method<&Constra::__construct>("__construct", {});
        constra.method<&Constra::__destruct>("__destruct", {});

        Php::Namespace unit("Components\\Gate\\Unit");
        Php::Class<unit::foo> foo("foo");
        Php::Class<unit::bar> bar("bar");

        // routeget.method<&RouteGet::test>("test", {});

        // constra.method<&Constra::test>("test", {});

        foo.method<&unit::foo::foo_u>("foo_u", {});
        bar.method<&unit::bar::bar_u>("bar_u", {});

        unit.add(std::move(foo));
        unit.add(std::move(bar));

        engine.method<&Engine::Framework>("Framework", {});
        engine.method<&Engine::Run>("Run", {});

        autoload.method<&Autoload::Config>("Config", {});
        autoload.method<&Autoload::Register>("Register", {});

        route.method<&Route::Get>("Get", {});
        route.method<&Route::Post>("Post", {});
        route.method<&Route::Put>("Put", {});
        route.method<&Route::Patch>("Patch", {});
        route.method<&Route::Delete>("Delete", {});
        route.method<&Route::Redirect>("Redirect", {});
        route.method<&Route::Any>("Any", {});

        routecontext.method<&RouteContext::code_501>("code_501", {});

        controller.method<&Controller::Class>("Class", {});
        
        request.method<&Request::__construct>("__construct", {});
        request.method<&Request::uri>("uri", {});
        request.method<&Request::get>("get", {});

        fusion.add(std::move(engine));
        fusion.add(std::move(autoload));
        fusion.add(std::move(route));
        fusion.add(std::move(routecontext));

        fusion.add(std::move(routeget));
        fusion.add(std::move(routepost));
        fusion.add(std::move(routeput));
        fusion.add(std::move(routepatch));
        fusion.add(std::move(routedelete));
        fusion.add(std::move(routeredirect));
        fusion.add(std::move(routeany));

        fusion.add(std::move(controller));
        fusion.add(std::move(request));
        fusion.add(std::move(unit));
        fusion.add(std::move(constra));

        extension.add(Php::Constant("FS_DEFAULT", "FS_DEFAULT"));
        extension.add(Php::Constant("FS_COMPACT", "FS_COMPACT"));

        // wrapped namespace, add to extension
        extension.add(std::move(fusion));

        return extension;
    }
}
