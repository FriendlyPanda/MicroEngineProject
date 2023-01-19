//
// Created by adamh on 17/01/2023.
//

#ifndef MEP_GAMECONFIGURATION_H
#define MEP_GAMECONFIGURATION_H


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

class GameConfiguration {
private:
    std::map<std::string, void *> settings;
public:
    GameConfiguration();
    bool loadFromFile(std::string path);
    bool saveToFile(std::string path);

    template <typename T>
    T * get(const std::string& key) {
        return (static_cast<T *>(settings[key]));
    }

    void set(const std::string& key, void * val);
    void remove(const std::string& key);
    void clean();
    void print();
    ~GameConfiguration();
};


#endif //MEP_GAMECONFIGURATION_H
