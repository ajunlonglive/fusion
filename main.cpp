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

        Php::Class<Engine> engine("Cores\\Engine");
        Php::Class<Autoload> autoload("Cores\\Autoload");
        Php::Class<Route> route("Controllers\\Route");
        Php::Class<Controller> controller("Controllers\\Controller");
        Php::Class<Request> request("Http\\Request");
        // Php::Class<InputCapture> inputcapture("Utils\\InputCapture");

        engine.method<&Engine::Framework>("Framework", {});
        engine.method<&Engine::Run>("Run", {});

        autoload.method<&Autoload::Config>("Config", {});
        autoload.method<&Autoload::Register>("Register", {});

        route.method<&Route::Get>("Get", {});

        controller.method<&Controller::Class>("Class", {});

        request.method<&Request::input>("input", {});

        // inputcapture.method<&InputCapture::is_capturable>("is_capturable", {});

        // adding class to namespace
        fusion.add(std::move(engine));
        fusion.add(std::move(autoload));
        fusion.add(std::move(route));
        fusion.add(std::move(controller));
        fusion.add(std::move(request));
        // fusion.add(std::move(inputcapture));

        extension.add(Php::Constant("FS_DEFAULT", "FS_DEFAULT"));
        extension.add(Php::Constant("FS_COMPACT", "FS_COMPACT"));

        // wrapped namespace, add to extension
        extension.add(std::move(fusion));

        return extension;
    }
}
