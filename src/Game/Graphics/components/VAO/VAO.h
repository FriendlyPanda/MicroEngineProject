//
// Created by User on 31/05/2023.
//

#ifndef MEP_VAO_H
#define MEP_VAO_H


#include "GL/glew.h"
#include "../VBO/VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();
    void VAO_create();

    void link_attribute(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void * offset);
    void bind();
    void unbind();
    void clear();

};


#endif //MEP_VAO_H
