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
#include <GL/glew.h>
#include <spdlog/logger.h>
#include "../InternalLogger.h"


std::string get_file_contents(const char *filename);

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
};


#endif //MEP_SHADER_H
