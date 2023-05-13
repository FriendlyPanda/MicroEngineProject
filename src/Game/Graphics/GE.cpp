//
// Created by JFH on 03/01/2023.
//

#include "GE.h"

GraphicsEngine::GraphicsEngine(spdlog::logger logger) : logger(logger) {
    msg = new MessageBoard("Assets/properties/messages_en.properties");
    logger.info(msg->get("msg.test"));
}

int GraphicsEngine::_run() {

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint programID = loadShaders("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glUseProgram(programID);
    do{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    return 0;
}

void GraphicsEngine::_close() {
    glfwDestroyWindow(window);

    glfwTerminate();
    logger.info(msg->get("graphics_engine.misc.close_success"));

}

int GraphicsEngine::_init() {
    if(!glfwInit()){
        logger.error(msg->get("graphics_engine.glfw.failed_init"));
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 768, "Tutorial 01",nullptr, nullptr);
    if(window == nullptr){
        logger.error(msg->get("graphics_engine.glfw.failed_window"));
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        logger.error(msg->get("graphics_engine.glew.failed_init"));
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    logger.info(msg->get("graphics_engine.misc.init_success"));
    return 0;
}

GraphicsEngine::~GraphicsEngine() {
    free(msg);
    msg = nullptr;
}

GLuint GraphicsEngine::loadShaders(const char *vertex_file_path, const char *fragment_file_path) {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        logger.error(msg->get("graphics_engine.misc.wrong_shader_filepath", {vertex_file_path}));
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }else{
        logger.error(msg->get("graphics_engine.misc.wrong_shader_filepath", {fragment_file_path}));
        return 0;
    }
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    logger.info(msg->get("graphics_engine.misc.compiling_shader", {vertex_file_path}));
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        logger.warn(msg->get("msg.empty", {&VertexShaderErrorMessage[0]}));
    }

    // Compile Fragment Shader
    logger.info(msg->get("graphics_engine.misc.compiling_shader", {fragment_file_path}));
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        logger.warn(msg->get("msg.empty", {&FragmentShaderErrorMessage[0]}));
    }

    // Link the program
    logger.info(msg->get("graphics_engine.shader.linking"));
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
        logger.warn(msg->get("msg.empty", {&ProgramErrorMessage[0]}));
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

