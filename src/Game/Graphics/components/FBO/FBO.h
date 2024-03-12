//
// Created by janha on 12/03/2024.
//

#ifndef MEP_FBO_H
#define MEP_FBO_H

#include "GL/glew.h"

class FBO {
    GLuint ID;
    FBO();
    void FBO_create();

    void bind();
    void unbind();
    void clear();
};


#endif //MEP_FBO_H
