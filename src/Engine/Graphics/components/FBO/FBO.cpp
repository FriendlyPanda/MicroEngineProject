//
// Created by janha on 12/03/2024.
//

#include "FBO.h"
#include "iostream"

FBO::FBO() {
    ID = 0;
}

void FBO::FBO_create(RBO newRBO, Texture newTexture) {
    glGenFramebuffers(1, &ID);
    GLenum error = glGetError();
    if(error!=GL_NO_ERROR){
        std::cout << "OpenGL Error: " << error;
        return;
    }
    bind();
    this->texture = newTexture;
    this->rbo = newRBO;
    linkTexture(this->texture);
    linkRBO(this->rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n" << std::endl;
    }
    unbind();
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

void FBO::linkRBO(RBO newRBO) {
    this->rbo = newRBO;
    rbo.bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo.ID);
    rbo.unbind();
}

void FBO::rescale(int width, int height) {
    texture.resize(width, height);
    rbo.resizeStorage(width, height);
    linkTexture(texture);
    linkRBO(rbo);
}

void FBO::linkTexture(Texture txtr) {
    this->texture = txtr;
    texture.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.ID, 0);
    texture.unbind();
}
