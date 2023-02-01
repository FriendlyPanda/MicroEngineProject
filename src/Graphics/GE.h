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
#else
#   error "Unknown Compiller"
#endif

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include "../Game/GameConfiguration.h"
#include "../Game/GameSprite.h"
//#include "../Game/GameSprite.h"

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480


class GraphicsEngine{
private:
    SDL_Window * geWindow;
    SDL_Event event{};
    bool exit = false;
    int imgFlags;
    GameSprite * geTexture;
    SDL_Renderer * geRenderer;
    SDL_Rect geRect;
    GameConfiguration * gc;
public:
    GraphicsEngine();
    GraphicsEngine(GameConfiguration * gameConfig);
    int _execute();
    void _close();
private:
    int _init();
    int _render();
    SDL_Texture * loadTexture(std::string path);
};



#endif //MEP_GE_H
