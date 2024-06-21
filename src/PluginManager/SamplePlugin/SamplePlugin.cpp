//
// Created by janha on 15/06/2024.
//
#include "PluginInterface.h"
#include <iostream>

class SamplePlugin : public PluginInterface {
public:

    PluginInterface* createPlugin(){
        return this;
    };

    void destroyPlugin(PluginInterface* plugin){
        if(plugin == this){
            shutdown_();
        }
    };

    void init_() override{
        plugin_error = PLUGIN_OK;
        plugin_step_mode = PLUGIN_SYNC;
        std::cout << "plugin init" << std::endl;
    }
    void shutdown_() override{
        std::cout << "plugin shutdown" << std::endl;
    }
    void step_(double delta_time) override{
        std::cout << "plugin " << steps << " step" << std::endl;
    }
    int get_error_() override{
        std::cout << "plugin get error" << std::endl;
        return plugin_error;
    }
    const char* get_error_message_() override{
        std::cout << "plugin get error message" << std::endl;
    }
     const char* get_name_() override{
         std::cout << "plugin get name" << std::endl;
         return "SamplePlugin";
    }

    // data exchange
    bool setData(const std::string& key, const std::any& data) override{
        std::cout << "plugin set data: " << data.type().name() << " at key: " << key << std::endl;
        return true;
    }
    [[nodiscard]] std::any getData(const std::string& key) const override{
        std::cout << "plugin get data at key: " << key << std::endl;
        return nullptr;
    }


private:
    int steps = 0;
};