#include "GameMisc.h"

/**
 * Helper function to make rectangles easier
 * @param x x positionAndDimention
 * @param y y positionAndDimention
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @return the complete rectangle
 */
SDL_Rect sdlRect(int x, int y, int w, int h) {
    SDL_Rect rectangle = SDL_Rect();
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    return rectangle;
}

/**
 * Helper function to make points easier
 * @param x x positionAndDimention
 * @param y y positionAndDimention
 * @return SDL_Point the complete point
 */
SDL_Point sdlPoint(int x, int y){
    SDL_Point point = SDL_Point();
    point.x = x;
    point.y = y;
    return point;
}

/**
 * Helper function to make rectangle from 2 points easier
 * @param p1 determines the x and y
 * @param p2 determines the w and h
 * @return SDL_Rect from 2 points
 */
SDL_Rect sdlRectFromPoints(SDL_Point p1, SDL_Point p2) {
    return sdlRect(p1.x, p1.y, p2.x, p2.y);
}