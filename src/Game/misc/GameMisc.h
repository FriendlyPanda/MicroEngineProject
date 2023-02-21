//
// Created by User on 13/02/2023.
//

#ifndef MEP_GAMEMISC_H
#define MEP_GAMEMISC_H


#include <type_traits>
#include "SDL_rect.h"


SDL_Rect sdlRectFromPoints(SDL_Point p1, SDL_Point p2);
SDL_Point sdlPoint(int x, int y);
SDL_Rect sdlRect(int x, int y, int w, int h);

#endif //MEP_GAMEMISC_H
