//
// Created by adamh on 03/01/2023.
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
#include <cstdio>

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

class GraphicsEngine{
private:
    SDL_Window * geWindow;
    SDL_Surface * geScreenSurface;
    SDL_Surface * geCurrentSurface;
    SDL_Event event;
    bool exit;
public:
    GraphicsEngine();
    int _execute();
private:
    int _init();
    int _render();
    void _close();
};



#endif //MEP_GE_H
