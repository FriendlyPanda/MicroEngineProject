//
// Created by JFH on 03/01/2023.
//

#include "GE.h"

GraphicsEngine::GraphicsEngine() {
    log.msg = new MessageBoard("Assets/properties/messages_en.properties");
    log.logger.info(log.msg->get("msg.test"));
    const char * vertexFilepath = "Assets/Shaders/vertex.glsl";
    const char * fragmentFilepath = "Assets/Shaders/fragment.glsl";

    shaderProgram = Shader(vertexFilepath, fragmentFilepath);

}

int GraphicsEngine::_run() {
    // set the clear colour
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    double lastTime = glfwGetTime();
    int nbFrames = 0;

    do{

        // Measure speed
        GLdouble currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0/GLdouble(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }
        // clear the screen with clear color
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.activate();
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    return 0;
}

void GraphicsEngine::_close() {
    glfwDestroyWindow(window);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shaderProgram.clear();
    glfwTerminate();
    log.logger.info(log.msg->get("graphics_engine.misc.close_success"));

}

int GraphicsEngine::_init() {
    // initialise glfw
    if(!glfwInit()){
        log.logger.error(log.msg->get("graphics_engine.glfw.failed_init"));
        return -1;
    }
    // set glfw samples, version and mode
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window using glfw
    window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Tutorial 01",nullptr, nullptr);
    if(window == nullptr){ // check if the window has successfully been created
        log.logger.error(log.msg->get("graphics_engine.glfw.failed_window"));
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){ // initialise glew and check if it initialised correctly
        log.logger.error(log.msg->get("graphics_engine.glew.failed_init"));
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // set up Vertex Array Object and Vertex Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    log.logger.info(log.msg->get("graphics_engine.misc.init_success"));
    return 0;
}

GraphicsEngine::~GraphicsEngine() {
    log.clear();
}

