//
// Created by janha on 14/03/2024.
//

#include "RBO.h"

RBO::RBO() {
}

void RBO::RBO_create(int width, int height) {
    glGenRenderbuffers(1, &ID);
    resizeStorage(width, height);
}


void RBO::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

void RBO::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RBO::clear() {
    glDeleteRenderbuffers(1, &ID);
}

void RBO::resizeStorage(int width, int height) {
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    unbind();
}
