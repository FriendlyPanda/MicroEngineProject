//
// Created by janha on 14/03/2024.
//

#ifndef MEP_TEXTURE_H
#define MEP_TEXTURE_H


#include "GL/glew.h"

class Texture {
public:
    GLuint ID;

    Texture();

    void texture_create(GLsizei width, GLsizei height);
    void bind();
    void unbind();
    void clear();
    void resize(GLsizei width, GLsizei height);

};


#endif //MEP_TEXTURE_H
