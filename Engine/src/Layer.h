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
        virtual void onUpdate();
        virtual void onEvent(Event& e);
        std::string getName() const
        {
            return this->name;
        }
    protected:
        std::string name;    
    };
};