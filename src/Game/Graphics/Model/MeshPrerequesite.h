//
// Created by janha on 05/03/2024.
//

#ifndef MEP_MESHPREREQUESITE_H
#define MEP_MESHPREREQUESITE_H

#include <string>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

#endif //MEP_MESHPREREQUESITE_H
