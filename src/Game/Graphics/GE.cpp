//
// Created by JFH on 03/01/2023.
//

#include "GE.h"

GraphicsEngine::GraphicsEngine() {
    log.msg = new MessageBoard("Assets/properties/messages_en.properties");
    log.logger.info(log.msg->get("msg.test"));
    // initialise glfw
    if (!glfwInit()) {
        log.logger.error(log.msg->get("graphics_engine.glfw.failed_init"));
        return;
    }
    // set glfw samples, version and mode
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window using glfw
    window = glfwCreateWindow(windowWidth, windowHeight, "BaseWindow", nullptr, nullptr);
    if (window == nullptr) { // check if the window has successfully been created
        log.logger.error(log.msg->get("graphics_engine.glfw.failed_window"));
        return;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) { // initialise glew and check if it initialised correctly
        log.logger.error(log.msg->get("graphics_engine.glew.failed_init"));
        return;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    shaderProgram = Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");

    // uniform variable - to send data to shaders

    uniID = shaderProgram.getUniform("scale");

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

    glViewport(0,0,windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    log.logger.info(log.msg->get("graphics_engine.misc.init_success"));
    init_success = true;
}

int GraphicsEngine::_run() {
    if(!init_success) {
        return -1;
    }
    // set the clear colour
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    shaderProgram.activate();
    vao.bind();

    GLfloat size = 0;

    // bind FPS to the screen refresh rate
    glfwSwapInterval(1);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        size += 0.01f;
        if(size > 2.0f) {
            size = 0;
        }
        glUniform1f(uniID, size);
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

GraphicsEngine::~GraphicsEngine() {
    log.clear();
}

