#pragma once
#include <phpcpp.h>

#include <transport/session/session.hpp>
#include <serfix/fileio.hpp>
#include <serfix/compiler.hpp>

#include <string>
#include <functional>
#include <dirent.h>

namespace cores {
    namespace autoload {

class c_loader : public Php::Base {
    private: void static m_list_files(const std::string &path, std::function<void(const std::string &)> cb) {
        if (auto dir = opendir(path.c_str())) {
            while (auto f = readdir(dir)) {
                if (!f->d_name || f->d_name[0] == '.')
                    continue;
                
                if (f->d_type == DT_DIR) 
                    m_list_files(path + f->d_name + "/", cb);

                if (f->d_type == DT_REG)
                    cb(path + f->d_name);
            }
            closedir(dir);
        }
    }

    private: void static m_require_src(Php::Value p_directory, bool only_once) {
        std::string directory = p_directory;
        m_list_files(directory, [&](const std::string &path) {
            if(only_once) {
                std::string source_code = serfix::fileio::read(path);
                std::string replaced = serfix::compile::code(source_code);
                std::string file_id = serfix::fileio::write(path, replaced);

                Php::require_once("../storage/fusion/cache/serfix/" +file_id);
                serfix::fileio::unlink("../storage/fusion/cache/serfix/" +file_id);
            } else {
                std::string source_code = serfix::fileio::read(path);
                std::string replaced = serfix::compile::code(source_code);
                std::string file_id = serfix::fileio::write(path, replaced);

                Php::require("../storage/fusion/cache/serfix/" +file_id);
                serfix::fileio::unlink("../storage/fusion/cache/serfix/" +file_id);
            }
        });
    }

    public: void static m_default() {
        // MVC client directory
        Php::Value app_config;
        
        app_config["FS_Framework_Dir"]["Config"]        = "../config/";
        app_config["FS_MVC_Client_Dir"]["Controllers"]  = "../app/Controllers/";
        app_config["FS_MVC_Client_Dir"]["Models"]       = "../app/Models/";
        // app_config["FS_MVC_Client_Dir"]["Views"]       = "../app/Views/";

        // Routes client directory
        app_config["FS_Routes_Client_Dir"] = "../routes/";

        transport::session::c_set::m_array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"}, app_config);
        
    }

 public: void static m_framework_config() {
        // Register the framework config as startup used for require_src
        Php::Value app_config = transport::session::c_get::m_array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"});
        
        m_require_src(app_config["FS_Framework_Dir"]["Config"], true);   
        
    }


    public: void static m_default_app() {
        // Register the default_app config as startup used for require_src
        Php::Value app_config = transport::session::c_get::m_array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"});

        m_require_src(app_config["FS_MVC_Client_Dir"]["Controllers"], true);   
        m_require_src(app_config["FS_MVC_Client_Dir"]["Models"], true);
        m_require_src(app_config["FS_MVC_Client_Dir"]["Views"], true);
        
    }

    public: void static m_route() {
        Php::Value app_config = transport::session::c_get::m_array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"});
        m_require_src(app_config["FS_Routes_Client_Dir"], false);
    }

};


    }
}