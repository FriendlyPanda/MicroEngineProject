//
// Created by JFH on 03/01/2023.
//

#include "GE.h"

GraphicsEngine::GraphicsEngine() {
    log.msg = new MessageBoard("Assets/properties/messages_en.properties");
    log.logger.info(log.msg->get("msg.test"));
}

int GraphicsEngine::_run() {
    // set the clear colour
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    do {

#ifdef NDEBUG
        // release version
#else
        //debug version
        // Measure speed
        GLdouble currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\t : \t %f fps\n", 1000.0 / GLdouble(nbFrames), GLdouble(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }
#endif

        // clear the screen with clear color
        //glClearColor(0.1f, 0.23f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.activate();
        glUniform1f(uniID, 1.0f);
        vao.bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    return 0;
}

void GraphicsEngine::_close() {
    glfwDestroyWindow(window);
    vao.clear();
    vbo.clear();
    ebo.clear();
    shaderProgram.clear();
    glfwTerminate();
    log.logger.info(log.msg->get("graphics_engine.misc.close_success"));

}

int GraphicsEngine::_init() {
    // initialise glfw
    if (!glfwInit()) {
        log.logger.error(log.msg->get("graphics_engine.glfw.failed_init"));
        return -1;
    }
    // set glfw samples, version and mode
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window using glfw
    window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "BaseWindow", nullptr, nullptr);
    if (window == nullptr) { // check if the window has successfully been created
        log.logger.error(log.msg->get("graphics_engine.glfw.failed_window"));
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) { // initialise glew and check if it initialised correctly
        log.logger.error(log.msg->get("graphics_engine.glew.failed_init"));
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    shaderProgram = Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");

    uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // set up Vertex Array Object and Vertex Buffer Object

    vao.VAO_create();
    vao.bind();

    vbo = VBO(vertices, sizeof(vertices));
    ebo = EBO(indices, sizeof(indices));

    vao.link_attribute(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)(0 * sizeof(float)));
    vao.link_attribute(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));



    vao.unbind();
    vbo.unbind();
    ebo.unbind();



    log.logger.info(log.msg->get("graphics_engine.misc.init_success"));
    return 0;
}

GraphicsEngine::~GraphicsEngine() {
    log.clear();
}

