//
// Created by janha on 15/06/2024.
//

#ifndef MEP_PLUGININTERFACE_H
#define MEP_PLUGININTERFACE_H

#include <string>
#include <vector>
#include <any>

// plugin state
#define PLUGIN_OK                       0
#define PLUGIN_ERROR_INIT               (1 << 0)
#define PLUGIN_ERROR_SHUTDOWN           (1 << 1)
#define PLUGIN_ERROR_INVALID_OPERATION  (1 << 2)

// plugin step mode
#define PLUGIN_SYNC             0
#define PLUGIN_ASYNC            (1 << 0)

class PluginInterface{
public:
    virtual ~PluginInterface() {}
    virtual void init_() = 0;
    virtual void shutdown_() = 0;
    virtual void step_(double delta_time) = 0;
    virtual int get_error_() = 0;
    virtual const char* get_error_message_() = 0;
    virtual const char* get_name_() = 0;

    // data exchange
    virtual bool setData(const std::string& key, const std::any& data) = 0;
    [[nodiscard]] virtual std::any getData(const std::string& key) const = 0;

    int plugin_error;
    int plugin_step_mode;
};

extern "C" PluginInterface* createPlugin();
extern "C" void destroyPlugin(PluginInterface* plugin);

#endif //MEP_PLUGININTERFACE_H
