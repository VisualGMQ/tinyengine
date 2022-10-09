#include "engine/core/init_config.hpp"

namespace engine {

std::unique_ptr<InitConfig> InitConfig::instance_;

#ifndef DEBUG_MODE
#include "init_config.inc"
#endif

InitConfig& InitConfig::Instance() {
    if (!instance_) {
        instance_ = std::make_unique<InitConfig>();
        instance_->ParseFile("init.toml");
    }
    return *instance_;
}

void InitConfig::ParseFile(std::string_view name) {
    title_ = "TinyEngine v0.1.0";
    size_.w = 1024;
    size_.h = 720;
    resizable_ = false;
    useSceneTree_ = false; 
    useConsole_ = false;
    isDrawColliderOutline_ = false;

    toml::table tbl;
    try {
#ifdef DEBUG_MODE
        tbl = toml::parse_file("./init.toml");
#else
        tbl = toml::parse(InitConfigContent);
#endif
        title_ = tbl["title"].value_or("TinyEngine v0.1.0");
        size_.w = tbl["width"].value_or(1024);
        size_.h = tbl["height"].value_or(720);
        resizable_ = tbl["resizable"].value_or(false);
        useSceneTree_ = tbl["use_scene_tree"].value_or(false);
        useConsole_ = tbl["use_console"].value_or(false);
        isDrawColliderOutline_ = tbl["draw_collider_outline"].value_or(false);
    } catch (const toml::parse_error& err) {
        Logw("parse init.toml failed, skip config");
    }
}

}
