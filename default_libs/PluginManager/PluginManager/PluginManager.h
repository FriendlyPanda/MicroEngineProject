//
// Created by janha on 15/06/2024.
//

#ifndef MEP_PLUGINMANAGER_H
#define MEP_PLUGINMANAGER_H


#include "PluginInterface.h"
#include <string>
#include <vector>
#include <memory>

#ifdef _WIN32
#include <windef.h>
#endif


// cross-platform plugin manager

class PluginManager {
public:
    /**
     * Load a specific plugin by filename
     * @param pluginName the name of the plugin with the .so/.dll extension
     * @return the success of loading the plugin
     */
    bool loadPlugin(const std::string& pluginName);

    /**
     * unload all plugins previously loaded, the plugin manager is not unloaded
     */
    void unloadPlugins();

    /**
     * Scan the default plugin location (Assets\\Plugins\\*.so/.dll) for plugins and load them depending on the operating system will load .so for linux and .dll for windows
     */
    void scanForPlugins();

    /**
     * returns the pointer to a plugin to be used in the code, the plugin needs a specified name for this to work
     * @param name name of the plugin/library
     * @return the pluginInterface pointer
     */
    PluginInterface* getPlugin(const std::string& name) const;

private:
    /**
     * plugin handler and instance struct
     */
    struct PluginHandle{
#ifdef _WIN32
        HMODULE handle;
#else
        void * handle;
#endif

        std::unique_ptr<PluginInterface> instance;
    };

    /**
     * the plugins used successfully loaded
     */
    std::vector<PluginHandle> plugins;

};


#endif //MEP_PLUGINMANAGER_H
