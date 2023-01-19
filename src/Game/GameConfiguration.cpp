//

// Created by adamh on 17/01/2023.
//

#include "GameConfiguration.h"
#include <iostream>


GameConfiguration::GameConfiguration() {

}

bool GameConfiguration::loadFromFile(std::string path) {
    bool success = true;
    return success;
}

bool GameConfiguration::saveToFile(std::string path) {
    bool success = true;
    return false;
}

void GameConfiguration::set(const std::string& key, void * val) {
    settings[key] = val;
}

void GameConfiguration::remove(const std::string& key) {
    settings[key] = nullptr;
    settings.erase(key);
}

void GameConfiguration::clean() {
    for(auto & setting : settings)
    {
        setting.second = nullptr;
    }
    settings.clear();
}

GameConfiguration::~GameConfiguration() {
    clean();
}

void GameConfiguration::print() {
    auto it = settings.begin();
    while(it != settings.end()){
        std::cout << "\t" << it->first << " : " << it->second << std::endl;
        ++it;
    }
}


