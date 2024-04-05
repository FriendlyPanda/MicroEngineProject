//
// Created by janha on 12/03/2024.
//

#ifndef MEP_FBO_H
#define MEP_FBO_H

#include "GL/glew.h"
#include "../RBO/RBO.h"
#include "../Texture/Texture.h"

class FBO {
public:
    GLuint ID;
    FBO();
    void FBO_create(RBO newRBO, Texture newTexture);
    RBO rbo;
    Texture texture;

    void bind();
    void unbind();
    void clear();
    void linkRBO(RBO rbo);
    void linkTexture(Texture txtr);
    void rescale(int width, int height);
};


#endif //MEP_FBO_H
