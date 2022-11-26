#pragma once

#include "../Layer.h"

namespace Azazel
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& e);
	};
}