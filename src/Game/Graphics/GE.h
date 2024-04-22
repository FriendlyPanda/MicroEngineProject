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
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../misc/InternalLogger.h"
#include "components/EBO/EBO.h"
#include "components/FBO/FBO.h"
#include "components/Model/Model.h"
#include "components/Shaders/Shader.h"
#include "components/VAO/VAO.h"
#include "components/VBO/VBO.h"
#include "components/camera/Camera.h"
#include "modules/GUIBaseClass.h"

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"


// OpenGL Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GraphicsEngine {
public:
	GraphicsEngine(GLFWwindow * window_ptr, FBO * fbo_ptr, MessageBoard * config_ptr, double * deltaTime);
	int init_();

	// temp testing function, remove before release
	void setShaderProgram(Shader newShaderProgram);

	void setUIRender(std::function<void()> * start, std::function<void()> * end);
private:

	// window settings
    GLFWwindow *window;
	int windowWidth;
	int windowHeight;

	// frame buffers
    FBO * fbo;
    RBO rbo;
    Texture txt;

	// temp testing parameters
    //Model mdl = Model("");

	// world view
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    Shader shaderProgram;
	double * deltaTime;


	// messages and logs
    MessageBoard * config;
    InternalLogger log = InternalLogger("Graphics");

	// UI
	GUIBaseClass * ui = nullptr;



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

//    void guiUpdateStart();
//    void guiUpdateEnd();
//    void initGUIcontext();
//    void closeGUIcontext();


public:
    bool init_success = false;
    GraphicsEngine();

    int _run();
    void _close();



    virtual ~GraphicsEngine();
};


#endif //MEP_GE_H
