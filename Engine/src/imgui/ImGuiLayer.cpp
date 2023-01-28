#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Application.h>
#include <Window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <events/ApplicationEvent.h>

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
