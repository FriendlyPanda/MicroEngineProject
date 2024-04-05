//
// Created by User on 31/05/2023.
//

#ifndef MEP_VBO_H
#define MEP_VBO_H


#include "GL/glew.h"

class VBO {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID;

    // Basic Constructors
    VBO();
    VBO(GLfloat * vertices, GLsizeiptr size);

    // Binds the VBO to the GL program
    void bind();

    // unbinds VBO from the GL program
    void unbind();

    // delete and clear memory
    void clear();
};


#endif //MEP_VBO_H
