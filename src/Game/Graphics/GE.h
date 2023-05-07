//
// Created by JFH on 03/01/2023.
//


#ifndef MEP_GE_H
#define MEP_GE_H



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //Windows based systems
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#elif __APPLE__
    // appple systems
#elif __linux__
    //linux based systems
#endif

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720

#include <cstdio>
#include <string>
#include "../GameConfiguration.h"
#include "../Nodes/GameObject.h"
#include "../Nodes/NodeSystem.h"

class GraphicsEngine{
private:
    //SDL_Window * geWindow;
    //SDL_Event event{};
    bool exit = false;
    int imgFlags{};
    GameObject * gameObject{};
    //SDL_Renderer * geRenderer;
    //SDL_Rect geRect;
    GameConfiguration * gc{};
    NodeSystem * nodeSys{};
    int tempFPS{};
public:
    GraphicsEngine();
    explicit GraphicsEngine(GameConfiguration * gameConfig);
    int _execute();
    void _close();
    int _init();
    void setNodeSystem(NodeSystem *);
};



#endif //MEP_GE_H
