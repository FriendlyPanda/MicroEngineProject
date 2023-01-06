//
// Created by adamh on 03/01/2023.
//


#ifndef MEP_GRAPHICENGINE_H
#define MEP_GRAPHICENGINE_H

#if _WIN64 || _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <SDL.h>


class GraphicsEngine{
private:
    SDL_Window * geWindow;
    SDL_Surface * geScreenSurface;
    SDL_Surface * geCurrentSurface;
    SDL_Event event;
    bool exit;

public:
    GraphicsEngine();
    void ge_execute();
private:
    bool ge_init();
    bool ge_render();
    void ge_close();
};

#endif //MEP_GRAPHICENGINE_H
