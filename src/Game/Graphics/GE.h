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


#include "../InternalLogger.h"
#include "Shader.h"

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

class GraphicsEngine{
private:
    GLFWwindow * window;
    GLuint VAO, VBO, EBO;
    Shader shaderProgram;
    InternalLogger log = InternalLogger("Graphics");
    GLfloat g_vertex_buffer_data[18]= {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
            -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
            0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
            0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };
    GLuint indicies[9] = {
            0,3,5,
            3,2,4,
            5,4,1
    };

public:
    GraphicsEngine();
    int _run();
    void _close();
    int _init();

    virtual ~GraphicsEngine();
};



#endif //MEP_GE_H
