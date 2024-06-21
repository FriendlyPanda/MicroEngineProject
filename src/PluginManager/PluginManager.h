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
    bool loadPlugin(const std::string& path);
    void unloadPlugins();

    PluginInterface* getPlugin(const std::string& name) const;

private:
    struct PluginHandle{
#ifdef _WIN32
        HMODULE handle;
#else
        void * handle;
#endif

        std::unique_ptr<PluginInterface> instance;
    };

    std::vector<PluginHandle> plugins;

};


#endif //MEP_PLUGINMANAGER_H
