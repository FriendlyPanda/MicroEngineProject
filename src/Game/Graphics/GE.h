//
// Created by JFH on 03/01/2023.
//


#ifndef MEP_GE_H
#define MEP_GE_H



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //Windows based systems
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#elif __APPLE__
    // appple systems
#elif __linux__
    //linux based systems
#endif

#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 720

#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "../../properties/MessageBoard.h"
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class GraphicsEngine{
private:
    GLFWwindow * window;
    MessageBoard * msg;
    spdlog::logger logger;
    GLuint VertexArrayID;
    constexpr static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };
public:
    GraphicsEngine(spdlog::logger logger);
    int _run();
    void _close();
    int _init();

    virtual ~GraphicsEngine();
private:
    GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
};



#endif //MEP_GE_H
