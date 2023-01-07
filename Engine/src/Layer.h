#pragma once

#include <string>
#include "events/Event.h"

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
        virtual void onImguiRender(float delta);
        virtual void onInputUpdate(float delta);
        virtual void onEvent(Event& e);
        inline std::string getName() const
        {
            return this->name;
        }
    protected:
        std::string name;    
    };
};