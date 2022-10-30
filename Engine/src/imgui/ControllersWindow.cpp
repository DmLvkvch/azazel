#include "ControllersWindow.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Azazel
{
	void ControllerWindow::draw()
	{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SliderFloat("Translation X", &translation.x, 0.0f, 940.0f);
        ImGui::SliderFloat("Translation Y", &translation.y, 0.0f, 560.0f);
        ImGui::SliderFloat("Translation Z", &translation.z, 0.0f, 560.0f);


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}