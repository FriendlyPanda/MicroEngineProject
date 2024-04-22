

#include <fstream>
#include "src/Game/Graphics/GE.h"

int main(int argc, char * args[]) {
	GLFWwindow *mainWindow;
	FBO * fbo;
	MessageBoard config = MessageBoard("Assets/properties/config.properties");


    GraphicsEngine ge(mainWindow, fbo, &config);
	ge.init_();

	Shader shaderProgram = Shader("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");
	ge.setShaderProgram(shaderProgram);

    ge._run();
    ge._close();

    return 0;
}