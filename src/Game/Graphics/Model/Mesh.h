//
// Created by janha on 05/03/2024.
//

#ifndef MEP_MESH_H
#define MEP_MESH_H

#include "MeshPrerequesite.h"
#include "../Shaders/Shader.h"
#include <vector>

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();

};


#endif //MEP_MESH_H
