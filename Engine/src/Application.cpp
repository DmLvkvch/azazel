#include "Application.h"
#include "events/ApplicationEvent.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Azazel
{
	Application* Application::app = nullptr;

	Application* Application::createApplication()
	{
		if (!Application::app)
		{
			Application::app = new Application();
		}
		return Application::app;
	}

	Application::Application()
	{
		lastFrameTime = 0.0f;
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event& e)
	{
		if (e.getEventType() == EventType::WindowClose)
		{
			running = false;
		}

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*(--it))->onEvent(e);
			if (e.handled)
			{
				break;
			}
		}
	}

	void Application::run()
	{
		while (running)
		{
			float t = (float) (glfwGetTime() * 1000);
			float delta = t - lastFrameTime;
			lastFrameTime = t;
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        	glClearColor(0.3f, 0.25f, 0.5f, 1.0f);
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();
			for (Layer* layer : layerStack)
			{
				layer->onUpdate(delta);
			}
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			window->onUpdate(delta);
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		layerStack.pushOverlay(layer);
	}

	Window* Application::getWindow()
	{
		return this->window.get();
	}

	Application* Application::get()
	{
		return Application::app;
	}
}