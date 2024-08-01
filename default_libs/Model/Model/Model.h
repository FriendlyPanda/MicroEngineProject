//
// Created by janha on 05/03/2024.
// Documentation Generated by Jetbrains AI
//

#ifndef MEP_MODEL_H
#define MEP_MODEL_H
#define STB_IMAGE_IMPLEMENTATION
#include "../Mesh/MeshPrerequesite.h"
#include "Shaders/Shader.h"
#include <vector>
#include "../Mesh/Mesh.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
#include <iostream>

/**
 * @brief Loads a texture from a file.
 *
 * @param path The path of the texture file.
 * @param directory The directory in which the texture file is located.
 * @param gamma Whether or not to apply gamma correction to the texture.
 * @return The ID of the loaded texture.
 */
unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    /**
     * @brief The Model class represents a 3D model loaded from a file.
     *
     * It stores information about the model's meshes, textures, and directory.
     * The model can be drawn using the Draw() method.
     */
    Model(char * path);
    /**
     * @fn void Draw(Shader &shader)
     * @brief Draw the model using the specified shader.
     *
     * This function renders the model using the specified shader program.
     * It iterates through all the meshes in the model and calls their respective Draw() functions, passing in the shader program.
     *
     * @param shader The shader program to use for rendering.
     */
    void Draw(Shader &shader);

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<ModelTexture> textures_loaded;

    /**
     * @brief Loads a model from the given file path using the ASSIMP library.
     *
     * @param path The file path of the model.
     */
//    void loadModel(std::string path);
    /**
     * @brief Process the given node in the model.
     *
     * This function processes each mesh located at the current node in the model scene.
     * It calls processMesh function for each mesh and adds the processed mesh to the meshes vector.
     * Then, it recursively process each of the children nodes.
     *
     * @param node The node to be processed.
     * @param scene The model scene.
     */
//    void processNode(aiNode *node, const aiScene *scene);
    /**
        * @brief Processes a mesh using the Assimp library.
        *
        * This function takes an aiMesh object and an aiScene object as parameters and processes the mesh data to create a Mesh object. It extracts the vertex positions, normals, texture coordinates, tangents, and bitangents from the aiMesh object and stores them in a vector of Vertex objects.
        * It also retrieves the vertex indices and stores them in a vector of unsigned integers. It processes the materials of the mesh to load the corresponding textures and stores them in a vector of ModelTexture objects. Finally, it creates a Mesh object using the extracted data and returns it.
        *
        * @param mesh The aiMesh object representing the mesh to be processed.
        * @param scene The aiScene object containing the scene information.
        * @return The processed Mesh object.
        */
//    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    /**
     * @brief Loads material textures from an aiMaterial.
     *
     * This function takes an aiMaterial, texture type, and texture type name as input.
     * It loads all textures of the specified type from the material and returns them as a vector of ModelTexture objects.
     *
     * @param mat The aiMaterial to load textures from.
     * @param type The aiTextureType to filter the textures.
     * @param typeName The name of the texture type.
     * @return std::vector<ModelTexture> A vector containing the loaded textures.
     *
     * @related Model
     * @see Model::loadMaterialTextures
     */
//    std::vector<ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};


#endif //MEP_MODEL_H