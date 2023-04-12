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
        dt += delta;
        n++;
        if (n % 10 == 0)
        {
            fps = 1000.0f * 10 / dt;
            n = 0;
            dt = 0;
        }
        ImGui::Text("Current FPS %.3f", 1000.0f / delta);
        ImGui::Text("Avg FPS %.3f", fps);

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
