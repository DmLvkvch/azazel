#pragma once

#include "Window.h"
#include <memory>
#include "LayerStack.h"

namespace Azazel
{
	class Application
	{
	public:
		Application();
		~Application();
		void run();
		void onEvent(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
		Window* getWindow();
		
		static Application* createApplication();
		static Application* getApplication();
	private:
		std::unique_ptr<Window> window;
		LayerStack layerStack;
		bool running = true;
		static Application* app;
		float lastFrameTime;
	};
}