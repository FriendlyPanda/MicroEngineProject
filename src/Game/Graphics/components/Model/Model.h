//
// Created by janha on 05/03/2024.
//

#ifndef MEP_MODEL_H
#define MEP_MODEL_H
#define STB_IMAGE_IMPLEMENTATION
#include "MeshPrerequesite.h"
#include "../Shaders/Shader.h"
#include <vector>
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    Model(char *path)
    {
        if(path != ""){
            loadModel(path);
        }
    }
    void Draw(Shader &shader);

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};


#endif //MEP_MODEL_H
