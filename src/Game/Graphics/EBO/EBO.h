//
// Created by User on 31/05/2023.
//

#ifndef MEP_EBO_H
#define MEP_EBO_H


#include "GL/glew.h"

class EBO {
public:
    GLuint ID;
    EBO();
    EBO(GLuint * indices, GLsizeiptr size);

    void bind();
    void unbind();
    void clear();

};


#endif //MEP_EBO_H
