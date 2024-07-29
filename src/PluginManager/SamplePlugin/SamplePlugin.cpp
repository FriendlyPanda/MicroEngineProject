//
// Created by janha on 15/06/2024.
//
#include "SamplePlugin.h"
#include <iostream>

extern "C" SamplePlugin* createPlugin(){
    return new SamplePlugin;
}

extern "C" void destroyPlugin(SamplePlugin* object){
    delete object;
}

void SamplePlugin::init_() {
    plugin_error = PLUGIN_OK;
    plugin_step_mode = PLUGIN_SYNC;
    std::cout << "plugin init" << std::endl;
}

void SamplePlugin::shutdown_() {
    std::cout << "plugin shutdown" << std::endl;
}
void SamplePlugin::step_(double delta_time) {
    std::cout << "plugin " << steps << " step" << std::endl;
}
int SamplePlugin::get_error_() {
    std::cout << "plugin get error" << std::endl;
    return plugin_error;
}
const char* SamplePlugin::get_error_message_() {
    std::cout << "plugin get error message" << std::endl;
    return "Sample error";
}

 const char* SamplePlugin::get_name_() {
     std::cout << "plugin get name" << std::endl;
     return PLUGIN_NAME;
}

// data exchange
bool SamplePlugin::setData(const std::string& key, const std::any& data){
    std::cout << "plugin set data: " << data.type().name() << " at key: " << key << std::endl;
    return true;
}

std::any SamplePlugin::getData(const std::string& key) const{
    std::cout << "plugin get data at key: " << key << std::endl;
    return nullptr;
}