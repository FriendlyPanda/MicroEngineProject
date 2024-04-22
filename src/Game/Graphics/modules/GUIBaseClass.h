//
// Created by User on 22/04/2024.
//

#ifndef MEP_GUIBASECLASS_H
#define MEP_GUIBASECLASS_H

#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class GUIBaseClass {
protected:
	/**
	 * The IO of the gui
	 */
	ImGuiIO io;

	/**
	 * the style of the gui
	 */
	ImGuiStyle style;

	/**
	 * the window the gui will be rendered to
	 */
	GLFWwindow * window = nullptr;

public:
	/**
	 * simple constructor with a default initialization procedure
	 */
	GUIBaseClass() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		this->io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsClassic();
		style = ImGui::GetStyle();
		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	/**
	 * an additional steps to the constructor that will allow for the class to be initialized before glfw and opengl context is created
	 * @param renderWindow the window to render the GUI in
	 */
	void init_ImGUI_window(GLFWwindow *renderWindow){
		if(renderWindow  != nullptr){
			this->window = renderWindow;
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}
	}

	/**
	 * An update start procedure
	 */
	virtual void gui_update_start() {}

	/**
	 * An update end procedure
	 */
	virtual void gui_update_end() {}

	/**
	 * A destructor that will check if the opengl and glfw have been initialized before shutting them down
	 */
	virtual ~GUIBaseClass() {
		if(window != nullptr) {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
		}
		ImGui::DestroyContext();
	}
};

#endif // MEP_GUIBASECLASS_H
