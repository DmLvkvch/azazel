#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Application.h"
#include "../Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Azazel
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::get()->getWindow()->getNativeWindow(), true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	}

	void ImGuiLayer::onDetach()
	{
	}

	void ImGuiLayer::onUpdate()
	{
	}

	void ImGuiLayer::onEvent(Event& e)
	{
	}
}
