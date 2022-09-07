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
        static Php::Extension extension("FusionEngine", "1.0");

        Php::Namespace fusion("Fusion");

        Php::Class<cores::c_engine>                                     cores_engine                                ("Cores\\Engine");
        Php::Class<cores::c_autoload>                                   cores_autoload                              ("Cores\\Autoload");
        
        Php::Class<controllers::c_controller>                           controllers_controller                      ("Controllers\\Controller");
        
        Php::Class<http::c_request>                                     http_request                                ("Http\\Request");

        Php::Class<components::gate::c_route>                           components_gate_route                       ("Components\\Gate\\Route");
        Php::Class<components::gate::route::c_route_context>            components_gate_route_route_context         ("Components\\Gate\\Route\\Context");
        Php::Class<components::gate::route::method::c_route_get>        components_gate_route_method_route_get      ("Components\\Gate\\Route\\Method\\Get");
        Php::Class<components::gate::route::method::c_route_post>       components_gate_route_method_route_post     ("Components\\Gate\\Route\\Method\\Post");
        Php::Class<components::gate::route::method::c_route_head>       components_gate_route_method_route_head     ("Components\\Gate\\Route\\Method\\Head");
        Php::Class<components::gate::route::method::c_route_put>        components_gate_route_method_route_put      ("Components\\Gate\\Route\\Method\\Put");
        Php::Class<components::gate::route::method::c_route_patch>      components_gate_route_method_route_patch    ("Components\\Gate\\Route\\Method\\Patch");
        Php::Class<components::gate::route::method::c_route_options>    components_gate_route_method_route_options  ("Components\\Gate\\Route\\Method\\Options");
        Php::Class<components::gate::route::method::c_route_redirect>   components_gate_route_method_route_redirect ("Components\\Gate\\Route\\Method\\Redirect");
        Php::Class<components::gate::route::method::c_route_any>        components_gate_route_method_route_any      ("Components\\Gate\\Route\\Method\\Any");
        Php::Class<components::gate::route::method::c_route_method>     components_gate_route_method_route_method   ("Components\\Gate\\Route\\Method\\Method");

        Php::Class<views::c_constra>                                    views_constra                               ("Views\\Constra");

        Php::Class<error::internal::error_handler>                      error_internal_error_handler                ("Error\\InternalPhp\\Handler");


        // Engine module dependencies
        cores_engine.method<&cores::c_engine::m_framework>("framework", {});
        cores_engine.method<&cores::c_engine::m_config>("config", {});
        cores_engine.method<&cores::c_engine::m_run>("run", {});

        // Autoload/Loader dependencies
        cores_autoload.method<&cores::c_autoload::m_config>("config", {});
        cores_autoload.method<&cores::c_autoload::m_register_config>("registConfig", {});
        cores_autoload.method<&cores::c_autoload::m_register_app>("registApp", {});


        // HTTP Request dependencies
        http_request.method<&http::c_request::__construct>("__construct", {});
        http_request.method<&http::c_request::m_url>("url", {});
        http_request.method<&http::c_request::m_path>("path", {});
        http_request.method<&http::c_request::m_full>("full", {});
        

        // Route method dependencies
        components_gate_route.method<&components::gate::c_route::m_get>("Get", {});
        components_gate_route.method<&components::gate::c_route::m_post>("Post", {});
        components_gate_route.method<&components::gate::c_route::m_head>("Head", {});
        components_gate_route.method<&components::gate::c_route::m_put>("Put", {});
        components_gate_route.method<&components::gate::c_route::m_patch>("Patch", {});
        components_gate_route.method<&components::gate::c_route::m_options>("Options", {});
        components_gate_route.method<&components::gate::c_route::m_redirect>("Redirect", {});
        components_gate_route.method<&components::gate::c_route::m_any>("Any", {});
        components_gate_route.method<&components::gate::c_route::m_method>("Method", {});

        // Route context dependencies
        components_gate_route_route_context.method<&components::gate::route::c_route_context::m_uri>("uri", {});
        components_gate_route_route_context.method<&components::gate::route::c_route_context::m_parse>("parse", {});


        // Constra dependencies
        views_constra.method<&views::c_constra::__construct>("__construct", {});
        views_constra.method<&views::c_constra::__destruct>("__destruct", {});


        // Internal PHP error handler dependencies
        error_internal_error_handler.method<&error::internal::error_handler::callback>("callback", {});


        fusion.add(std::move(cores_engine));
        fusion.add(std::move(cores_autoload));

        fusion.add(std::move(controllers_controller));

        fusion.add(std::move(http_request));

        fusion.add(std::move(components_gate_route_method_route_get));
        fusion.add(std::move(components_gate_route_method_route_post));
        fusion.add(std::move(components_gate_route_method_route_head));
        fusion.add(std::move(components_gate_route_method_route_put));
        fusion.add(std::move(components_gate_route_method_route_patch));
        fusion.add(std::move(components_gate_route_method_route_options));
        fusion.add(std::move(components_gate_route_method_route_redirect));
        fusion.add(std::move(components_gate_route_method_route_any));
        fusion.add(std::move(components_gate_route_method_route_method));

        fusion.add(std::move(components_gate_route));
        fusion.add(std::move(components_gate_route_route_context));

        fusion.add(std::move(views_constra));
        
        fusion.add(std::move(error_internal_error_handler));

        fusion.add<&error::internal::fusion_php_error_handler>("Error\\InternalPhp\\FusionErrorHandler");

        extension.add(Php::Constant("FS_DEFAULT", "FS_DEFAULT"));
        extension.add(Php::Constant("FS_COMPACT", "FS_COMPACT"));
        extension.add(Php::Constant("safe_html",  "htmlspecialchars"));
        extension.add(Php::Constant("upper_case", "strtoupper"));
        extension.add(Php::Constant("lower_case", "strtolower"));

        extension.add<echos>("echos");
        extension.add<views::constra::f_minifier>("constra_minifier");
        extension.add<views::constra::f_e>("e");
        extension.add<reflector>("reflector");

        // wrapped namespace, add to extension
        extension.add(std::move(fusion));

        return extension;
    }
}
