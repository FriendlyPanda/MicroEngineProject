//
// Created by janha on 14/03/2024.
//

#ifndef MEP_RBO_H
#define MEP_RBO_H



#include "GL/glew.h"


class RBO {
public:
    GLuint ID;
    RBO();
    void RBO_create(int width, int height);

    void bind();
    void unbind();
    void clear();
    void resizeStorage(int width, int height);
};


#endif //MEP_RBO_H
