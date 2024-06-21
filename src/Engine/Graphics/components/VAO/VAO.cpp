//
// Created by User on 31/05/2023.
//

#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
}

// Links a VBO to the VAO using a certain layout
void VAO::link_attribute(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void * offset) {
    vbo.bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

// Binds the VAO
void VAO::bind()
{
    glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::unbind() {
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::clear() {
    glDeleteVertexArrays(1, &ID);
}

void VAO::VAO_create() {
    glGenVertexArrays(1, &ID);
}
