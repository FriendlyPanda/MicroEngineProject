//
// Created by adamh on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_render() {

    //get updates
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit = true;
        }
    }

    return 0;

}