//
// Created by janha on 14/03/2024.
//

#include "Texture.h"

Texture::Texture() {
}


void Texture::texture_create(GLsizei width, GLsizei height) {
    glGenTextures(1, &ID);
    resize(width, height);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clear() {
    glDeleteTextures(1, &ID);
}


void Texture::resize(GLsizei width, GLsizei height) {
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unbind();
}
