//
// Created by User on 01/03/2023.
//

#ifndef MEP_GRAPHICALENGINE_H
#define MEP_GRAPHICALENGINE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include "../../properties/MessageBoard.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#define WIDTH 800
#define HEIGHT 600

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class GraphicalEngine {
public:
    void run(){
        initWindow();
        spdlog::info(messages->get("vulkan.begin"));
        initVulkan();
        mainLoop();
        cleanup();
    };

    void setMessageBoard(MessageBoard * messageBoard){
        messages = messageBoard;
    }
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void createInstance();
    static std::vector<const char*> getRequiredExtensions();
    static bool checkValidationLayerSupport();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
            void * pUserData){
        std::cout << "Validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }
    void setupDebugMessenger();
private:
    MessageBoard * messages;
    GLFWwindow * window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
};


#endif //MEP_GRAPHICALENGINE_H
