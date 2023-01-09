//
// Created by adamh on 08/01/2023.
//

#include "GE.h"

void GraphicsEngine::_close() {
    SDL_FreeSurface(geCurrentSurface);
    geCurrentSurface = nullptr;
    SDL_FreeSurface(geScreenSurface);
    geScreenSurface = nullptr;
    SDL_DestroyWindow(geWindow);
    geWindow = nullptr;

    SDL_Quit();
}