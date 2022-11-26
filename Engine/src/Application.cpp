#include "Application.h"
#include "events/ApplicationEvent.h"
#include <iostream>
namespace Azazel
{
	Application* Application::app = nullptr;

	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event& e)
	{
		std::cout<<e.toString()<<std::endl;
		if (e.getEventType() == EventType::WindowClose)
		{
			running = false;
		}

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->onEvent(e);
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

			for (Layer* layer : layerStack)
			{
				layer->onUpdate();
			}
			window->onUpdate();
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
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

	Application* Application::createApplication()
	{
		if (Application::app == nullptr)
		{
			Application::app = new Application();
		}
		return Application::app;
	}
}