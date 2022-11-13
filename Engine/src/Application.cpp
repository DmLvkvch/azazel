#include "Application.h"
#include "events/ApplicationEvent.h"

namespace Azazel
{
	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (true)
		{
			window->onUpdate();
		}
	}

	Application* Application::createApplication()
	{
		return new Application();
	}
}