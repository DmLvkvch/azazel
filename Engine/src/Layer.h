#pragma once

#include <string>
#include "events/Event.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Azazel
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();
        virtual void onAttach();
        virtual void onDetach();
        virtual void onUpdate(float delta);
        virtual void onRender(float delta);
        virtual void onImguiRender(float delta);
        virtual void onInputUpdate(float delta);
        virtual void onEvent(Event& e);
        const inline std::string getName() const
        {
            return this->name;
        }
    protected:
        std::string name;    
    };
};