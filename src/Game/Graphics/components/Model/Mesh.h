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
    // mesh Data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    GLuint VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
private:
    GLuint VBO, EBO;
    void setupMesh();

};


#endif //MEP_MESH_H
