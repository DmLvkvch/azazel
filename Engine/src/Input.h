#pragma once

#include <utility>

namespace Azazel
{
    class Input
    {
    public:
        Input();
        virtual ~Input();
        virtual bool isKeyPressed(int keycode);
        virtual bool isMouseButtonPressed(int button);
        virtual bool IsIsKeyHeld(int keycode);
        virtual std::pair<float, float> getMousePosition();
        static Input* getInput();
    private:
        static Input* input;
    };
}