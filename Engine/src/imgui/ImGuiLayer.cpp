#include "ImGuiLayer.h"

#include "Application.h"
#include "window/Window.h"
#include "events/ApplicationEvent.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "IO/Input.h"
#include <iostream>
#include "render/Render.h"

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
        ImGui::Text("Current FPS %d", static_cast<int>(1000.0f / delta));
        ImGui::Text("Avg FPS %d", static_cast<int>(fps));
        auto camera = Render::getRender()->getCamera();
        glm::vec3 cameraPos = camera->getViewPosition();
        ImGui::Text("Camera position: (%.3f, %.3f, %.3f)", cameraPos.x, cameraPos.y, cameraPos.z);

        glm::vec3 cameraDir = camera->getViewDirection();
        ImGui::Text("Camera direction: (%.3f, %.3f, %.3f)", cameraDir.x, cameraDir.y, cameraDir.z);
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
