//
// Created by janha on 05/03/2024.
//

#ifndef MEP_MESHPREREQUESITE_H
#define MEP_MESHPREREQUESITE_H

#include <string>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct ModelTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

#endif //MEP_MESHPREREQUESITE_H
