//
// Created by adamh on 17/01/2023.
//

#ifndef MEP_GAMECONFIGURATION_H
#define MEP_GAMECONFIGURATION_H

#ifndef NDEBUG
// debug code
#include "spdlog/spdlog.h"
#endif


#include <string>
#include <iostream>

#include <map>
#include <any>
#include "SDL.h"

/*
 * This class holds configuration of the game, available globally
 */


/*
 * BANNED TYPES -> working type replacement:
 *
 *  char        -> std::string
 */


/**
 * This config contains keys for the GameConfiguration, if a setting needs to be added, add key and then value
 *
 * negative numbers = read/save values to a file
 * positive values = assign values on runtime
 */
enum config {
    SCREEN_HEIGHT = -2,
    SCREEN_WIDTH = -1,
    FILLER = 0,
    RENDER,
    GAME_SPEED
};


class GameConfiguration {
private:
    std::map<config, void *> settings;
public:
    GameConfiguration();
    bool loadFromFile(std::string path);
    bool saveToFile(std::string path);

    template <typename T>
    T * get(config key) {
        return (static_cast<T *>(settings[key]));
    }

    void set(config key, void * val);
    void remove(config key);
    void clean();
    void print();
    ~GameConfiguration();
};


#endif //MEP_GAMECONFIGURATION_H
