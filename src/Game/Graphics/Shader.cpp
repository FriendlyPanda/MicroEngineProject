//
// Created by jan on 5/25/23.
//

#include "Shader.h"

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
    if (vertexFile == nullptr || fragmentFile == nullptr) {

    } else {
        ID = loadShaders(vertexFile, fragmentFile);
    }

}

GLuint Shader::loadShaders(const char *vertex_file_path, const char *fragment_file_path) {

    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1); // or handle the error in a nicer way
    if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
        exit(2); // or handle the error in a nicer way

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        log.logger.error(log.msg->get("graphics_engine.shader.wrong_filepath", {vertex_file_path}));
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    } else {
        log.logger.error(log.msg->get("graphics_engine.shader.wrong_filepath", {fragment_file_path}));
        return 0;
    }
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    log.logger.info(log.msg->get("graphics_engine.shader.compiling_shader", {vertex_file_path}));
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        log.logger.warn(log.msg->get("msg.empty", {&VertexShaderErrorMessage[0]}));
    }

    // Compile Fragment Shader
    log.logger.info(log.msg->get("graphics_engine.shader.compiling_shader", {fragment_file_path}));
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        log.logger.warn(log.msg->get("msg.empty", {&FragmentShaderErrorMessage[0]}));
    }

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
