//
// Created by janha on 15/06/2024.
//

#include "PluginManager.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

bool PluginManager::loadPlugin(const std::string &pluginName) {
    const std::string path = "Assets/Plugins/" + pluginName;
    PluginHandle pluginHandle;

#ifdef _WIN32
    //TODO: Add the create and destroy plugin checks for windows release

    pluginHandle.handle = LoadLibrary(path.c_str());
    if(!pluginHandle.handle){
        std::cerr << "Failed to load plugins: " << path << std::endl;
        return false;
    }

    auto createPlugin = reinterpret_cast<PluginInterface*(*)()>(
            GetProcAddress(pluginHandle.handle, "createPlugin"));
    auto destroyPlugin = reinterpret_cast<void(*)(PluginInterface*)>(
            GetProcAddress(pluginHandle.handle, "destroyPlugin"));
#else
    pluginHandle.handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!pluginHandle.handle) {
        std::cerr << "Failed to load plugin: " << dlerror() << std::endl;
        return false;
    }

    dlerror();

    auto createPlugin = (PluginInterface *(*)())(
            dlsym(pluginHandle.handle, "createPlugin"));
    if (!createPlugin) {
        std::cerr << "Failed to find plugin functions: " << dlerror() << std::endl;
        dlclose(pluginHandle.handle);
        return false;
    }

    auto destroyPlugin = (void (*)(PluginInterface *))(dlsym(pluginHandle.handle, "destroyPlugin"));
    if (!destroyPlugin) {
        std::cerr << "Failed to find plugin functions: " << dlerror() << std::endl;
        dlclose(pluginHandle.handle);
        return false;
    }

#endif

    //TODO: Remove this section due to lack of error info return
//    if(!createPlugin || !destroyPlugin) {
//        std::cerr << "Failed to find plugin functions: " << path << ": " << dlerror() << std::endl;
//#ifdef _WIN32
//        FreeLibrary(pluginHandle.handle);
//#else
//        dlclose(pluginHandle.handle);
//#endif
//        return false;
//    }

            pluginHandle.instance.reset(createPlugin());
            plugins.push_back(std::move(pluginHandle));
            return true;
}

void PluginManager::unloadPlugins() {
    for(auto& pluginHandle : plugins){
        if(pluginHandle.instance){
            auto destroyPlugin = reinterpret_cast<void(*)(PluginInterface*)>(
#ifdef _WIN32
                    GetProcAddress(pluginHandle.handle, "destroyPlugin")
#else
                    dlsym(pluginHandle.handle, "destroyPlugin")
#endif
                    );
            destroyPlugin(pluginHandle.instance.release());
#ifdef _WIN32
            FreeLibrary(pluginHandle.handle);
#else
            dlclose(pluginHandle.handle);
#endif
        }
    }
    plugins.clear();
}

PluginInterface *PluginManager::getPlugin(const std::string &name) const {
    for (const auto& pluginHandle : plugins) {
        if (pluginHandle.instance && name == pluginHandle.instance->get_name_()){
            return pluginHandle.instance.get();
        }
    }
    return nullptr;
}
