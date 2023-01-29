#pragma once

#include <utility>
#include <memory>

namespace Azazel
{
    class Input
    {
    public:
        Input();
        virtual ~Input();
        virtual bool isKeyPressed(int keycode);
        virtual bool isMouseButtonPressed(int button);
        virtual bool isKeyHeld(int keycode);
        virtual std::pair<float, float> getMousePosition();
        static Input* getInput();
    private:
        static std::unique_ptr<Input> input;
    };
}