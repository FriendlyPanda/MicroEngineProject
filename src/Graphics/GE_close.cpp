//
// Created by JFH on 08/01/2023.
//

#include "GE.h"

void GraphicsEngine::_close() {
    SDL_DestroyTexture(geTexture);
    SDL_DestroyRenderer(geRenderer);
    SDL_DestroyWindow(geWindow);

    geTexture = nullptr;
    geRenderer = nullptr;
    geWindow = nullptr;

    SDL_Quit();
}