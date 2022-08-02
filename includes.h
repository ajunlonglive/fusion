/**
 * @file include.h
 * @author Sultan Ilham (me@onecthree.id)
 * @brief Include header dependencis
 * @version 0.1
 * @date 2022-06-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <phpcpp.h>

#include <fusion/cores/engine/engine.hpp>
#include <fusion/cores/autoload/autoload.hpp>   

#include <fusion/components/gate/route/route.hpp>
#include <fusion/components/gate/route/context.hpp>

#include <fusion/controllers/controller/controller.hpp>
#include <fusion/http/request/input-capture.hpp>
#include <fusion/components/gate/route/unit.hpp>

#include <fusion/components/gate/route/method/get.hpp>
#include <fusion/components/gate/route/method/post.hpp>
#include <fusion/components/gate/route/method/head.hpp>
#include <fusion/components/gate/route/method/put.hpp>
#include <fusion/components/gate/route/method/patch.hpp>
#include <fusion/components/gate/route/method/delete.hpp>
#include <fusion/components/gate/route/method/options.hpp>
#include <fusion/components/gate/route/method/redirect.hpp>
#include <fusion/components/gate/route/method/any.hpp>

#include <fusion/views/constra/constra.hpp>
#include <fusion/cores/container/container.hpp>