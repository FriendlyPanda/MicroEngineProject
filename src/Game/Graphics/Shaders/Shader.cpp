//
// Created by jan on 5/25/23.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <regex>

std::string Shader::get_file_contents(const char *filename) {
    if (std::ifstream in(filename, std::ios::binary); in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    log.logger.error(log.msg->get("graphics_engine.shader.wrong_filepath", {filename}));
    throw errno;
}

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
    if (vertexFile == nullptr || fragmentFile == nullptr) {

    } else {
        ID = loadShaders(vertexFile, fragmentFile);
    }

}

void Shader::compile_shader(const std::string& sourceCode, const GLuint shaderID, GLint * Result, int * InfoLogLength) {
    // Compile Shader
    char const *sourcePointer = sourceCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, nullptr);
    glCompileShader(shaderID);

    // Check Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, InfoLogLength);
    if (*InfoLogLength > 0) {
        std::vector<char> shaderErrorMessage(*InfoLogLength + 1);
        glGetShaderInfoLog(shaderID, *InfoLogLength, nullptr, &shaderErrorMessage[0]);
        log.logger.warn(log.msg->get("msg.empty", {&shaderErrorMessage[0]}));
    }
}

GLuint Shader::loadShaders(const char *vertex_file_path, const char *fragment_file_path) {

    //extractUniforms(vertex_file_path);
    //extractUniforms(fragment_file_path);
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;

    // Create the shaders
    const GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    const GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    const std::string VertexShaderCode = get_file_contents(vertex_file_path);

    // Read the Fragment Shader code from the file
    const std::string FragmentShaderCode = get_file_contents(fragment_file_path);


    // Compile Vertex Shader
    log.logger.info(log.msg->get("graphics_engine.shader.compiling_shader", {vertex_file_path}));
    compile_shader(VertexShaderCode, VertexShaderID, &Result, &InfoLogLength);

    // Compile Fragment Shader
    log.logger.info(log.msg->get("graphics_engine.shader.compiling_shader", {fragment_file_path}));
    compile_shader(FragmentShaderCode, FragmentShaderID, &Result, &InfoLogLength);


    // Link the program
    log.logger.info(log.msg->get("graphics_engine.shader.linking"));
    const GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        log.logger.warn(log.msg->get("msg.empty", {&ProgramErrorMessage[0]}));
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    uniformVarManager.scanFile(vertex_file_path, ProgramID);
    uniformVarManager.scanFile(fragment_file_path, ProgramID);

    return ProgramID;
}

void Shader::activate() const {
    glUseProgram(ID);
}

void Shader::clear() const {
    glDeleteProgram(ID);
}

Shader::Shader() {
    ID = 0;
}

GLuint Shader::getUniform(const std::string& key) {
    return uniformVarManager.getUniform(key);
}

