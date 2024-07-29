//
// Created by jelly on 29/07/24.
//

#ifndef MEP_SAMPLEPLUGIN_H
#define MEP_SAMPLEPLUGIN_H

#include "PluginInterface.h"
#include "iostream"

#define PLUGIN_NAME "SamplePlugin"

class SamplePlugin : public PluginInterface {
public:
    void init_() override;

    void shutdown_() override;
    void step_(double delta_time) override;
    int get_error_() override;
    const char* get_error_message_() override;
    const char* get_name_() override;

    // data exchange
    bool setData(const std::string& key, const std::any& data) override;
    std::any getData(const std::string& key) const override;

private:
    int steps = 0;
};

#endif //MEP_SAMPLEPLUGIN_H
