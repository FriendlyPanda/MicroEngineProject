//
// Created by jan on 5/25/23.
//

#include "Shader.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <fstream>
#include <spdlog/logger.h>

std::string Shader::get_file_contents(const char *filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in) {
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

void Shader::compile_shader(const std::string& sourceCode, GLuint shaderID, GLint Result, int InfoLogLength) {
    // Compile Shader
    char const *sourcePointer = sourceCode.c_str();
    glShaderSource(shaderID, 1, &sourcePointer, nullptr);
    glCompileShader(shaderID);

    // Check Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> shaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shaderID, InfoLogLength, nullptr, &shaderErrorMessage[0]);
        log.logger.warn(log.msg->get("msg.empty", {&shaderErrorMessage[0]}));
    }
}

GLuint Shader::loadShaders(const char *vertex_file_path, const char *fragment_file_path) {

    GLint Result = GL_FALSE;
    int InfoLogLength = 0;

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode = get_file_contents(vertex_file_path);

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode = get_file_contents(fragment_file_path);


    // Compile Vertex Shader
    log.logger.info(log.msg->get("graphics_engine.shader.compiling_shader", {vertex_file_path}));
    compile_shader(VertexShaderCode, VertexShaderID, Result, InfoLogLength);

    // Compile Fragment Shader
    log.logger.info(log.msg->get("graphics_engine.shader.compiling_shader", {fragment_file_path}));
    compile_shader(FragmentShaderCode, FragmentShaderID, Result, InfoLogLength);


    // Link the program
    log.logger.info(log.msg->get("graphics_engine.shader.linking"));
    GLuint ProgramID = glCreateProgram();
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

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void Shader::activate() {
    glUseProgram(ID);
}

void Shader::clear() {
    glDeleteProgram(ID);
}

Shader::Shader() {
    ID = 0;
}

std::vector<std::string> Shader::extractUniforms(const std::string& filename) {
    std::vector<std::string> uniformVariables;

    // Read shader source file
    std::ifstream shaderFile(filename);
    if (!shaderFile.is_open()) {
        std::cerr << "Error opening shader file." << std::endl;
        return uniformVariables;
    }

    // Read the entire file into a string
    const std::string shaderSource((std::istreambuf_iterator<char>(shaderFile)),
                                   std::istreambuf_iterator<char>());
    shaderFile.close();

    // Define a regular expression to match uniform declarations
    const std::regex uniformRegex(R"(\buniform\s+\w+\s+(\w+);)");

    // Search for matches in the shader source
    std::smatch match;
    auto it = shaderSource.cbegin();
    const auto end = shaderSource.cend();

    while (std::regex_search(it, end, match, uniformRegex)) {
        // Extract the variable name from the match
        std::string variableName = match[1].str();

        // Add the variable name to the list
        uniformVariables.push_back(variableName);

        // Update iterator for the next search
        it = match.suffix().first;
    }

    return uniformVariables;
}

