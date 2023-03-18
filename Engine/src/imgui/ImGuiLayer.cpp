#include "ImGuiLayer.h"

#include "Application.h"
#include "window/Window.h"
#include "events/ApplicationEvent.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "IO/Input.h"
#include <iostream>

namespace Azazel
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
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

    void ImGuiLayer::onInputUpdate(float delta)
    {

    }

    void ImGuiLayer::onUpdate(float delta)
    {
        ImGui::Begin("Debug");
     
        ImGui::Text("FPS %.3f", 1000.0f / delta);

        ImGui::End();
    }

    void ImGuiLayer::onEvent(Event& e)
    {
        if (e.getEventType() == EventType::WindowResize)
        {
            const WindowResizeEvent& k = *(WindowResizeEvent*)&e;
            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2((float) k.getWidth(), (float) k.getHeight());
        }
    }
}
