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
#define PLUGIN_EVENT            (1 << 1)

/*
 * NOTE: not all functions are required, however it is important to keep track which are implemented
 */

class PluginInterface{
public:
    /**
     * basic plugin destructor
     */
    virtual ~PluginInterface() {}

    /**
     * plugin initializer
     * @param data the data to be used for initialisation of the plugin
     */
    virtual void init_(const std::vector<std::any>& data) = 0;

    /**
     * plugin shutdown, used for asynchronous plugins
     */
    virtual void shutdown_() = 0;
    /**
     * A step call, allowing for the sync and event driven plugins to send and receive data
     * @param data the data to send to the plugin
     * @return the data returning from the plugin
     */
    virtual std::vector<std::any> step_(const std::vector<std::any>& data) = 0;
    /**
     * basic error handling, works for a state of a plugin only
     * @return error code
     */
    virtual int get_error_() = 0;
    /**
     * The returner of error messages in human readable format
     * @return error message
     */
    virtual const char* get_error_message_() = 0;
    /**
     * plugin name returner
     * @return plugin name
     */
    virtual const char* get_name_() = 0;

    // async plugin
    /**
     * Set the data that the plugin has, the implementation is left for the plugin developer
     * @param data the data to send to the async plugin
     * @return
     */
    virtual void setData(const std::vector<std::any>& data) = 0;

    /**
     * the data returner for an asynchronous plugin
     * @return the data
     */
    virtual std::vector<std::any> getData() const = 0;

    // basic variables
    /**
     * error handling
     */
    int plugin_error;
    /**
     * step mode (sync/async/event)
     */
    int plugin_step_mode;
};

extern "C" PluginInterface* createPlugin();
extern "C" void destroyPlugin(PluginInterface* plugin);

#endif //MEP_PLUGININTERFACE_H
