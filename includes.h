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

#include <fusion/cores/engine/engine.cpp>
#include <fusion/cores/autoload/autoload.cpp>   
#include <fusion/components/gate/route/route.h>
#include <fusion/controllers/controller/controller.cpp>
#include <fusion/http/request/input-capture.h>
#include <fusion/components/gate/route/unit.cpp>
#include <fusion/components/gate/route/method/get.hpp>
#include <fusion/components/gate/route/method/post.hpp>
#include <fusion/components/gate/route/method/put.hpp>
#include <fusion/components/gate/route/method/delete.hpp>
#include <fusion/components/gate/route/method/patch.hpp>
#include <fusion/views/constra/constra.h>
#include <fusion/cores/container/container.h>