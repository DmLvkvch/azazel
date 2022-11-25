#pragma once

#include "Window.h"
#include <memory>

namespace Azazel
{
	class Application
	{
	public:
		Application();
		~Application();
		void run();
		void onEvent(Event& e);

		static Application* createApplication();
	private:
		std::unique_ptr<Window> window;

		bool running = true;
	};
}