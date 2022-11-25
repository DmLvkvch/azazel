#include "Application.h"
#include "events/ApplicationEvent.h"
#include <iostream>
namespace Azazel
{
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
	}

	void Application::run()
	{
		while (running)
		{
			window->onUpdate();
		}
	}

	Application* Application::createApplication()
	{
		return new Application();
	}
}