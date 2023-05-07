//
// Created by User on 13/02/2023.
//

#ifndef MEP_GAMEMISC_H
#define MEP_GAMEMISC_H


#include <type_traits>

/**
 * Basic point class
 */
class O_Point{
public:

    O_Point(float *x, float *y) : x(x), y(y) {}

    float * X() const {
        return x;
    }

    float * Y() const {
        return y;
    }

private:
    float *x;
    float *y;
};


class O_Rect{
public:
    O_Rect( O_Point origin,  O_Point dimensions);

    const O_Point &getOrigin() const;

    void setOrigin(const O_Point &origin);

    const O_Point &getDimensions() const;

    void setDimensions(const O_Point &dimensions);

private:
    O_Point origin;
    O_Point dimensions;
};

O_Rect points_to_rect(O_Point p1, O_Point p2);
O_Rect rect(float * x, float * y, float * w, float * h);


#endif //MEP_GAMEMISC_H
