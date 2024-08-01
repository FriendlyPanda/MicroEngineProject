

#include <fstream>
#include "src/Engine/Graphics/GE.h"
#include "default_plugins/SplineGen3D/SplineGen3D/SplineGenerator3D.h"
#include "PluginManager/PluginManager.h"

using namespace glm;

int main(int argc, char * args[]) {

    PluginManager pluginManager;

    pluginManager.loadPlugin("libSplineGen3D.so");
    auto samplePlugin = pluginManager.getPlugin("SplineGen3D");
    std::cout << samplePlugin->get_name_() << std::endl;
    samplePlugin->setData("sampleKey", {10});
    samplePlugin = nullptr;
    pluginManager.unloadPlugins();



	GLFWwindow * mainWindow = nullptr;
	FBO fbo = FBO();
	MessageBoard config = MessageBoard("Assets/properties/config.properties");
    config.update("window.enable_vsync", "0");
    config.save();

    double deltaTime = 0.0f;

    vec3 pointA{1.0, 1.0, 0.0};
    vec3 pointB{1.0, 0.0, 1.0};
    vec3 pointC{-1.0, 1.0, 1.0};
    vec3 pointD{-1.0, 0.0, 0.0};

    SplineGenerator3D spl{pointA, pointB, pointC, pointD, 20};


    GraphicsEngine ge(&fbo, &config, &deltaTime);
	ge.init_();
    mainWindow = ge.getWindow();

    spl.generateBezierCurve(20, 0.2f);

	auto * shaderProgram = new Shader(&config,"Assets/Shaders/temp/vertex.glsl", "Assets/Shaders/temp/fragment.glsl");


	ge.setShaderProgram(shaderProgram);
    ge.setMesh(spl.getMesh());

    ge._run();
    ge._close();

    return 0;
}