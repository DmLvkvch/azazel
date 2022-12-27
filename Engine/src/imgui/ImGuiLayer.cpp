#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Application.h"
#include "../Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../events/ApplicationEvent.h"

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

	}

	void ImGuiLayer::onDetach()
	{

	}

	void ImGuiLayer::onUpdate(float delta)
	{
		float x = 0.0f;
        ImGui::SliderFloat("translation", &x, -1.0f, 1.0f);
        ImGui::SliderFloat("rotation", &x, 0.0f, 360.0f);
        ImGui::SliderFloat("scale", &x, 0.0f, 10.0f);
	}

	void ImGuiLayer::onEvent(Event& e)
	{
		std::cout<<"imgui "<<e.toString()<<std::endl;
		 if (e.getEventType() == EventType::WindowResize)
        {
            const WindowResizeEvent& k = *(WindowResizeEvent*)&e;
            ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2(k.getWidth(), k.getHeight());
        }
	}
}
