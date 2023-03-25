#pragma once

#include "Camera.h"
#include "events/Events.h"
#include "Application.h"

namespace Azazel
{
    class CameraController
    {
        CameraController(Camera* camera)
        {
            index = Application::getApplication()->subscribe(std::bind(&CameraController::onEvent, this, std::placeholders::_1));
        }

        ~CameraController()
        {

        }

        void unsubscribe()
        {
            Application::getApplication()->unsubscribe(index);
        }

        void subscribe()
        {
            index = Application::getApplication()->subscribe(std::bind(&CameraController::onEvent, this, std::placeholders::_1));
        }

        void onUpdate(float delta)
        {

        }

        Camera* getCamera()
        {
            return camera;
        }
        void setCamera(Camera* camera)
        {
            this->camera = camera;
        }

        void onEvent(Event& e)
        {

        }

    private:
        int index = -1;
        Camera* camera;
    };
}