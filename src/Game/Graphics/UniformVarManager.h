//
// Created by janha on 19/02/2024.
//

#ifndef MEP_UNIFORMVARMANAGER_H
#define MEP_UNIFORMVARMANAGER_H


#include <unordered_map>
#include <string>
#include <vector>
#include <variant>
#include "GL/glew.h"

class UniformVarManager {
    std::pmr::unordered_map<std::string, GLuint> uniforms;
    int uniformLength;
public:
    UniformVarManager();
    void scanFile(const std::string& filename, GLuint shaderID);
    int getUniformLength() const;
    std::vector<std::string> getUniformList();
    int setUniform(const std::string&, GLuint);

    GLuint getUniform(const std::string& uniformName);
};


#endif //MEP_UNIFORMVARMANAGER_H
