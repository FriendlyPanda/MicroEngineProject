#include "GameMisc.h"

/**
 * Helper function to make rectangles easier
 * @param x origin positionAndDimention
 * @param y dimensions positionAndDimention
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @return the complete rectangle
 */
O_Rect rect(float * x, float * y, float * w, float * h) {
    return {O_Point(x,y),  O_Point(w,h)};
}

/**
 * Helper function to make rectangle from 2 points easier
 * @param p1 determines the origin and dimensions
 * @param p2 determines the w and h
 * @return O_Rect from 2 O_Points
 */
O_Rect points_to_rect(O_Point p1, O_Point p2) {
    return {p1, p2};
}

O_Rect::O_Rect(O_Point origin, O_Point dimensions) : origin(origin), dimensions(dimensions) {}

const O_Point &O_Rect::getOrigin() const {
    return origin;
}

void O_Rect::setOrigin(const O_Point &origin) {
    O_Rect::origin = origin;
}

const O_Point &O_Rect::getDimensions() const {
    return dimensions;
}

void O_Rect::setDimensions(const O_Point &dimensions) {
    O_Rect::dimensions = dimensions;
}
