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

#include "components/Shaders/Shader.h"
#include "components/VBO/VBO.h"
#include "components/VAO/VAO.h"
#include "components/EBO/EBO.h"
#include "../InternalLogger.h"
#include "components/Model/Model.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


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

//    Model mdl = Model("");

    const int windowWidth = DEFAULT_SCREEN_WIDTH;
    const int windowHeight = DEFAULT_SCREEN_HEIGHT;

    ImGuiIO io;
    ImGuiIO dockWindow;
    ImGuiIO viewWindow;
    ImGuiStyle style;

    Shader shaderProgram;

    GLuint uniID;

    InternalLogger log = InternalLogger("Graphics");

    GLfloat vertices[48] = {
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,        // 0  black
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,        // 1  blue
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,     // 2  green
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,      // 3  cyan
            -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,   // 4  red
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,   // 5  magenta
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,   // 6  yellow
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f     // 7  white
    };

    GLuint indices[36] = {
            0,1,3,
            0,2,3,
            0,2,6,
            0,1,4,
            0,4,6,
            1,4,5,
            1,3,5,
            2,3,7,
            2,6,7,
            3,5,7,
            4,5,6,
            5,6,7
    };

    GLfloat vertices2[36] = {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.5f, 0.8f, 0.3f, 0.9f,          // 0 Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,         // 1 Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f,   // 2 Upper corner
            -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f, // 3 Inner left
            0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,  // 4 Inner right
            0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f      // 5 Inner down
    };
    GLuint indices2[9] = {
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

    void guiUpdateStart();
    void guiUpdateEnd();
    void initGUIcontext();
    void closeGUIcontext();


public:
    bool init_success = false;
    GraphicsEngine();

    int _run();
    void _close();



    virtual ~GraphicsEngine();
};


#endif //MEP_GE_H
