//
// Created by JFH on 03/01/2023.
//

#include <iostream>
#include <utility>
#include "GE.h"
#include "../../properties/SafeConversion.cpp"

GraphicsEngine::GraphicsEngine() {


    shaderProgram = Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");



    //mdl = Model((char *) config->get("test.model").c_str());


//    initGUIcontext();


}

int GraphicsEngine::_run() {
    if(!init_success) {
        return -1;
    }
    // set the clear colour
    glClearColor(0.34f, 0.34f, 0.34f, 0.0f);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    shaderProgram.activate();

    // bind FPS to the screen refresh rate
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    rbo.RBO_create(windowWidth, windowHeight);
    txt.texture_create(windowWidth, windowHeight);
    fbo->FBO_create(rbo, txt);

    do {
        glfwPollEvents();
		if(ui != nullptr){
			ui->gui_update_start();
		}

		*deltaTime = glfwGetTime() - lastTime;

        fbo->bind();
#ifdef NDEBUG
        // release version
#else
        //debug version
        // Measure speed
        nbFrames++;
        if (*deltaTime >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\t : \t %f fps\n", 1000.0 / GLdouble(nbFrames), GLdouble(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }
#endif

        // clear the screen with clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shaderProgram.setMat4("model", model);
        //mdl.Draw(shaderProgram);

        fbo->unbind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(ui != nullptr){
			ui->gui_update_end();
		}

        glfwSwapBuffers(window);

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    return 0;
}


void GraphicsEngine::_close() {
    glfwDestroyWindow(window);
    fbo = nullptr;
    txt.clear();
    rbo.clear();
//    closeGUIcontext();
    shaderProgram.clear();
    glfwTerminate();
    log.logger.info(log.msg->get("graphics_engine.close"));
	log.clear();

}

GraphicsEngine::~GraphicsEngine() {
    log.clear();
}

//void GraphicsEngine::guiUpdateStart() {
//    // Start the Dear ImGui frame
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//
//    ImGui::NewFrame();
//    //ImGui::ShowDemoWindow(); // Show demo window! :)
//    ImGui::Begin("My Scene");
//
//    const float window_width = ImGui::GetContentRegionAvail().x;
//    const float window_height = ImGui::GetContentRegionAvail().y;
//
//    fbo->rescale(window_width, window_height);
//
//    glViewport(0,0,window_width, window_height);
//
//    ImVec2 pos = ImGui::GetCursorScreenPos();
//
//    ImGui::GetWindowDrawList()->AddImage(
//            (void *)fbo->texture.ID,
//            ImVec2(pos.x, pos.y),
//            ImVec2(pos.x + window_width, pos.y + window_height),
//            ImVec2(0, 1),
//            ImVec2(1, 0)
//            );
//
//    // render gui widgets
//    ImGui::End();
//    ImGui::Render();
//}

//void GraphicsEngine::guiUpdateEnd() {
////    // render the objects in the window
////    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//    // and we have to pass the render data further
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//        GLFWwindow* backup_current_context = glfwGetCurrentContext();
//        ImGui::UpdatePlatformWindows();
//        ImGui::RenderPlatformWindowsDefault();
//        glfwMakeContextCurrent(backup_current_context);
//    }
//}


//void GraphicsEngine::initGUIcontext() {
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    io = ImGui::GetIO();
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
//
////    ImGui::StyleColorsClassic();
////    style = ImGui::GetStyle();
////    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
////        style.WindowRounding = 0.0f;
////        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
////    }
//
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init();
//}

//void GraphicsEngine::closeGUIcontext() {
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//}

GraphicsEngine::GraphicsEngine(GLFWwindow *window_ptr, FBO *fbo_ptr, MessageBoard *config_ptr, double * deltaTime) {
	this->window = window_ptr;
	this->config = config_ptr;
	this->windowWidth = stringToIntSafe(const_cast<char *>(config->get("window.width").c_str()), DEFAULT_SCREEN_WIDTH);
	this->windowHeight = stringToIntSafe(const_cast<char *>(config->get("window.height").c_str()), DEFAULT_SCREEN_HEIGHT);
	this->log.msg = new MessageBoard(config->get("messages.graphics"));
	this->fbo = fbo_ptr;
	this->deltaTime = deltaTime;
}
int GraphicsEngine::init_() {
	// initialise glfw
	if (!glfwInit()) {
		log.logger.error(log.msg->get("glfw.failed_init"));
		return -1;
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
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) { // initialise glew and check if it initialised correctly
		log.logger.error(log.msg->get("glew.failed_init"));
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glViewport(0,0,windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	log.logger.info(log.msg->get("graphics_engine.init.success"));
	init_success = true;
	return 0;
}
void GraphicsEngine::setShaderProgram(Shader newShaderProgram) {
	this->shaderProgram = std::move(newShaderProgram);
	if(!shaderProgram.success){
		log.logger.error(log.msg->get("graphics_engine.init.fail"));
		init_success = false;
	}
}
//void GraphicsEngine::setUIRender(std::function<void()> * start, std::function<void()> * end) {
//	this->uiStart = start;
//	this->uiEnd = end;
//}
