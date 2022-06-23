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


        engine.method<&Engine::Framework>("Framework", {});


        // adding class to namespace
        fusion.add(std::move(engine));

        // wrapped namespace, add to extension
        extension.add(std::move(fusion));

        return extension;
    }
}
