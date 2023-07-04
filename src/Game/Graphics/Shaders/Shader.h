//
// Created by jan on 5/25/23.
//

#ifndef MEP_SHADER_H
#define MEP_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "GL/glew.h"
#include <spdlog/logger.h>
#include "../../InternalLogger.h"




class Shader {
public:
    GLuint ID;

    Shader(const char *vertexFile, const char *fragmentFile);

    Shader();

    void activate();

    void clear();

private:
    InternalLogger log = InternalLogger("Shaders");

    GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

    std::string get_file_contents(const char *filename);

    void compile_shader(const std::string& sourceCode, GLuint shaderID, GLint result, int InforLogLength);

};


#endif //MEP_SHADER_H
