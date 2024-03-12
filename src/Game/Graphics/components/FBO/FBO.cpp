//
// Created by janha on 12/03/2024.
//

#include "FBO.h"

FBO::FBO() {
}

void FBO::FBO_create() {
    glGenFramebuffers(1, &ID);
}

void FBO::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FBO::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::clear() {
    glDeleteFramebuffers(1, &ID);
}
