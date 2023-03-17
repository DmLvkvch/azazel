#include "CameraController.h"

#include "IO/Input.h"

namespace Azazel
{
    CameraController::CameraController()
    {

    }

    CameraController::~CameraController()
    {

    }

    void CameraController::onUpdate(float delta)
    {
        if (Input::getInput()->isKeyPressed(65))
        {
            camera.move({ -10.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(68))
        {
            camera.move({ 10.0f, 0.0f });
        }
        if (Input::getInput()->isKeyPressed(87))
        {
            camera.move({ 0.0f, 10.0f });
        }
        if (Input::getInput()->isKeyPressed(83))
        {
            camera.move({ 0.0f, -10.0f });
        }
    }
}