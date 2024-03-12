//
// Created by JFH on 03/01/2023.
//

#include <iostream>
#include "GE.h"

GraphicsEngine::GraphicsEngine() {
    // load messages
    log.msg = new MessageBoard("Assets/properties/messages_en.properties");

    // initialise glfw
    if (!glfwInit()) {
        log.logger.error(log.msg->get("glfw.failed_init"));
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
        log.logger.error(log.msg->get("glfw.failed_window"));
        return;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) { // initialise glew and check if it initialised correctly
        log.logger.error(log.msg->get("glew.failed_init"));
        return;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    shaderProgram = Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");

    if(!shaderProgram.success){
        log.logger.error(log.msg->get("graphics_engine.init.fail"));
        return;
    }

    // uniform variable - to send data to shaders

    uniID = shaderProgram.getUniform("transforms");

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

//    mdl = Model("C:/Users/janha/Documents/cube model/untitled.obj");

    glViewport(0,0,windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initGUIcontext();

    log.logger.info(log.msg->get("graphics_engine.init.success"));
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

    glEnable(GL_DEPTH_TEST);

    do {
        glfwPollEvents();
        guiUpdateStart();
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

        shaderProgram.activate();

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.5f, 0.5f));

        glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        shaderProgram.setMat4("projection", projection);
//        shaderProgram.setMat4("view", view);

//        mdl.Draw(shaderProgram);

        guiUpdateEnd();

        glfwSwapBuffers(window);

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    return 0;
}


void GraphicsEngine::_close() {
    glfwDestroyWindow(window);
    vao.clear();
    vbo.clear();
    ebo.clear();
    closeGUIcontext();
    shaderProgram.clear();
    glfwTerminate();
    log.logger.info(log.msg->get("graphics_engine.close"));

}

GraphicsEngine::~GraphicsEngine() {
    log.clear();
}

void GraphicsEngine::guiUpdateStart() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)
    ImGui::Begin("My Scene");
    // render gui widgets
    ImGui::End();
    ImGui::Render();
}

void GraphicsEngine::guiUpdateEnd() {
    // render the objects in the window
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // and we have to pass the render data further
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}


void GraphicsEngine::initGUIcontext() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
//    dockWindow = ImGui::GetIO();
//    viewWindow = ImGui::GetIO();
    io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsClassic();
    style = ImGui::GetStyle();
    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void GraphicsEngine::closeGUIcontext() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


