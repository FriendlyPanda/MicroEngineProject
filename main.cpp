

#include <fstream>
#include "src/Game/Graphics/GE.h"
#include "src/generators/SplineGenerator3D.h"

using namespace glm;

int main(int argc, char * args[]) {
	GLFWwindow *mainWindow;
	FBO fbo = FBO();
	MessageBoard config = MessageBoard("Assets/properties/config.properties");

    double deltaTime = 0.0f;

    vec3 pointA{1.0, 1.0, 0.0};
    vec3 pointB{1.0, 0.0, 1.0};
    vec3 pointC{-1.0, 1.0, 1.0};
    vec3 pointD{-1.0, 0.0, 0.0};

    SplineGenerator3D spl{pointA, pointB, pointC, pointD};


    GraphicsEngine ge(mainWindow, &fbo, &config, &deltaTime);
	ge.init_();

    spl.generateBezierCurve(20, 0.2f);

	Shader shaderProgram = Shader("Assets/Shaders/temp/vertex.glsl", "Assets/Shaders/temp/fragment.glsl");


	ge.setShaderProgram(shaderProgram);
    ge.setMesh(spl.getMesh());

    ge._run();
    ge._close();

    return 0;
}