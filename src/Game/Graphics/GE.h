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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shaders/Shader.h"
#include "VBO/VBO.h"
#include "VAO/VAO.h"
#include "EBO/EBO.h"
#include "../InternalLogger.h"

// OpenGL Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GraphicsEngine {
private:
    GLFWwindow *window;

    VAO vao;
    VBO vbo;
    EBO ebo;

    const int windowWidth = DEFAULT_SCREEN_WIDTH;
    const int windowHeight = DEFAULT_SCREEN_HEIGHT;

    Shader shaderProgram;

    GLuint uniID;

    InternalLogger log = InternalLogger("Graphics");
    GLfloat vertices[36] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f, // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f // Inner down
    };
    GLuint indices[9] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    static void framebuffer_size_callback(GLFWwindow * window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    static void windowResizeHandler(GLFWwindow * window, int windowWidth, int windowHeight){
        const float aspectRatio = ((float)windowWidth) / ((float)windowHeight);
        float xSpan = 1; // Feel free to change this to any xSpan you need.
        float ySpan = 1; // Feel free to change this to any ySpan you need.

        if (aspectRatio > 1){
            // Width > Height, so scale xSpan accordinly.
            xSpan *= aspectRatio;
        }
        else{
            // Height >= Width, so scale ySpan accordingly.
            ySpan = xSpan / aspectRatio;
        }
        glOrtho(-1*xSpan, xSpan, -1*ySpan, ySpan, -1, 1);

        // Use the entire window for rendering.
        glViewport(0, 0, windowWidth, windowHeight);
    }


public:
    bool init_success = false;
    GraphicsEngine();

    int _run();
    void _close();



    virtual ~GraphicsEngine();
};


#endif //MEP_GE_H
