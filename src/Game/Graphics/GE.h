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

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include <cstdio>
#include <string>
#include "../GameConfiguration.h"
#include "../Nodes/NodeSprite.h"
#include "../Nodes/GameObject.h"
#include "../Nodes/NodeSystem.h"
//#include "../Game/NodeSprite.h"

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720


class GraphicsEngine{
private:
    SDL_Window * geWindow;
    SDL_Event event{};
    bool exit = false;
    int imgFlags;
    GameObject * gameObject;
    SDL_Renderer * geRenderer;
    SDL_Rect geRect;
    GameConfiguration * gc;
    std::vector<NodeSprite *> spriteList;
    NodeSystem * nodeSys;
    int tempFPS;
public:
    GraphicsEngine();
    GraphicsEngine(GameConfiguration * gameConfig);
    GraphicsEngine(GameConfiguration * gameConfig, std::vector<NodeSprite *> newSpriteList);
    int _execute();
    void _close();
    int _init();
    void setNodeSystem(NodeSystem *);
private:
    int _render();
    SDL_Texture * loadTexture(std::string path);

    Uint8 min(int a, int b);
};



#endif //MEP_GE_H
