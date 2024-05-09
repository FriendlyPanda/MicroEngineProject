//
// Created by JFH on 03/01/2023.
//

#include <iostream>
#include <utility>
#include "GE.h"
#include "../../properties/MessageBoardConversion.h"

GraphicsEngine::GraphicsEngine(FBO * fbo_ptr, MessageBoard * config_ptr, double * deltaTime) {
    this->config = config_ptr;
    this->windowWidth = stringToIntSafe(const_cast<char *>(config->get("window.width").c_str()), DEFAULT_SCREEN_WIDTH);
    this->windowHeight = stringToIntSafe(const_cast<char *>(config->get("window.height").c_str()), DEFAULT_SCREEN_HEIGHT);
    this->log.setupMessageBoard(config->get("messages.graphics"));
    this->fbo = fbo_ptr;
    this->deltaTime = deltaTime;
    shaderProgram = nullptr;
}

int GraphicsEngine::init_() {
    if(log.getMessageBoard() == nullptr){
        log.error("init failed, aborting");
        return -1;
    }
    // initialise glfw
    if (!glfwInit()) {
        log.errorMsg("glfw.failed_init");
        return -1;
    }

    // set glfw samples, version and mode
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create a window using glfw
    window = glfwCreateWindow(windowWidth, windowHeight, "BaseWindow", nullptr, nullptr);
    if (window == nullptr) { // check if the window has successfully been created
        log.errorMsg("glfw.failed_window");
        return -1;
    }
    glfwMakeContextCurrent(window);

    auto testWindowPointer = window;

    if (glewInit() != GLEW_OK) { // initialise glew and check if it initialised correctly
        log.errorMsg("glew.failed_init");
        return -1;
    }

    if(testWindowPointer != window){
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glViewport(0,0,windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    log.infoMsg("graphics_engine.init.success");
    init_success = true;

    return 0;
}

int GraphicsEngine::_run() {
    if(!init_success) {
        log.errorMsg("graphics_engine.run.init.fail");
        return -1;
    }
    log.infoMsg("graphics_engine.run.start");
    // set the clear colour
    glClearColor(0.34f, 0.34f, 0.34f, 0.0f);

    double lastDeltaTime = glfwGetTime();
    double timepass = glfwGetTime();
    int nbFrames = 0;
    shaderProgram->activate();
    log.infoMsg("graphics_engine.run.shader.activated");

    // bind FPS to the screen refresh rate
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    log.infoMsg("graphics_engine.run.framebuffer.init.start");
    rbo.RBO_create(windowWidth, windowHeight);
    txt.texture_create(windowWidth, windowHeight);
    fbo->FBO_create(rbo, txt);
    log.infoMsg("graphics_engine.run.framebuffer.init.end");

    log.infoMsg("graphics_engine.run.loop.start");
    do {
        glfwPollEvents();
		if(ui != nullptr){
			ui->gui_update_start();
		}
		*deltaTime = glfwGetTime() - lastDeltaTime;
        fbo->bind();
#ifdef NDEBUG
        // release version
        lastDeltaTime = glfwGetTime();
#else
        //debug version
        // Measure speed
        timepass += *deltaTime;
        nbFrames++;
        if (timepass >= 1.0) { // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\t : \t %f fps\n", 1000.0 / GLdouble(nbFrames), GLdouble(nbFrames));
            nbFrames = 0;
            timepass = 0;
        }
#endif

        // clear the screen with clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        shaderProgram->setMat4("projection", projection);
        shaderProgram->setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shaderProgram->setMat4("model", model);

        glUniform3fv(shaderProgram->getUniform("color"), 1, glm::value_ptr(color));
        glUniform1fv(shaderProgram->getUniform("transparency"), 1, &transparency);

        //mdl.Draw(shaderProgram);

        fbo->unbind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(ui != nullptr){
			ui->gui_update_end();
		}
        mesh->Draw(*shaderProgram);

        glfwSwapBuffers(window);

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    log.infoMsg("graphics_engine.run.loop.end");
    return 0;
}


void GraphicsEngine::_close() {
    glfwDestroyWindow(window);
    fbo->clear();
    fbo = nullptr;
    txt.clear();
    rbo.clear();
    if(ui!= nullptr){
        ui->gui_close_context();
    }
    shaderProgram->clear();
    glfwTerminate();
    log.infoMsg("graphics_engine.close");
}

GraphicsEngine::~GraphicsEngine() {
    log.clear();
}


GraphicsEngine::GraphicsEngine() {
    window = nullptr;
    windowWidth = 0;
    windowHeight = 0;
    fbo = nullptr;
    deltaTime = nullptr;
    config = nullptr;
    shaderProgram = nullptr;
}




void GraphicsEngine::setShaderProgram(Shader * newShaderProgram) {
    if(newShaderProgram != nullptr){
        this->shaderProgram = newShaderProgram;
        if(!shaderProgram->checkSuccess()){
            log.errorMsg("graphics_engine.shader.linking.fail");
            init_success = false;
            return;
        }
        log.infoMsg("graphics_engine.shader.linking.success");
    }
}

void GraphicsEngine::setMesh(Mesh *newMesh) {
    mesh = newMesh;
}

bool GraphicsEngine::checkSuccess() const {
    return init_success;
}

GLFWwindow *GraphicsEngine::getWindow() {
    return window;
}

void GraphicsEngine::setUI(GUIBaseClass *gui) {
    if(gui != nullptr){
        this->ui = gui;
        ui->init_ImGUI_window(window);
    }
}

void GraphicsEngine::addNode(Node *newNode) {
    if(std::find(nodeIDs.begin(), nodeIDs.end(), newNode->getID()) != nodeIDs.end()){
        log.warning("The ID of a node is already reserved");
    }else{
        rootNode.addNode(newNode);
        nodeIDs.push_back(newNode->getID());
    }
}

void GraphicsEngine::removeNode(int ID) {

    auto it = std::find(nodeIDs.begin(), nodeIDs.end(), ID);

    if(it != nodeIDs.end()){
        rootNode.removeNode(ID);
        nodeIDs.erase(it);
    }else{
        log.warning("The ID does not exist");
    }
}

Node * GraphicsEngine::getNode(int ID) {
    return rootNode.getNode(ID);
}

Node_Object * GraphicsEngine::getNodeObject(const std::string& name) {
    for(unsigned int i : nodeIDs){
        Node * node = rootNode.getNode(i);
        if(typeid(*node) == typeid(Node_Object)){
            auto * node_obj = dynamic_cast<Node_Object *>(node);
            if(node_obj->getName() == name){
                return node_obj;
            }
        }
    }
    return nullptr;
}
