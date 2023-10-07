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
            //float cameraSpeed = static_cast<float>(2.5 * delta) / 1000.0f;
            //if (Input::getInput()->isKeyPressed(KEY_W))
            //{
            //    moveForward(cameraSpeed);
            //}
            //if (Input::getInput()->isKeyPressed(KEY_S))
            //{
            //    moveForward(-cameraSpeed);
            //}
            //if (Input::getInput()->isKeyPressed(KEY_A))
            //{
            //    moveRight(cameraSpeed);
            //}
            //if (Input::getInput()->isKeyPressed(KEY_D))
            //{
            //    moveRight(-cameraSpeed);
            //}
            //if (Input::getInput()->isKeyPressed(KEY_Q))
            //{
            //    moveUp(cameraSpeed);
            //}
            //if (Input::getInput()->isKeyPressed(KEY_E))
            //{
            //    moveUp(-cameraSpeed);
            //}
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
            //if (e.getEventType() == EventType::MouseScrolled)
            //{
            //    const MouseScrollEvent& ev = *(MouseScrollEvent*)(&e);
            //    zoomCamera(ev.getY());
            //}
            //if (e.getEventType() == EventType::MousePressed)
            //{
            //    lock = true;
            //}
            //if (e.getEventType() == EventType::MouseReleased)
            //{
            //    lock = false;
            //}
            //if (e.getEventType() == EventType::MouseMoved)
            //{
            //    const MouseMovedEvent& ev = *(MouseMovedEvent*)(&e);
            //    float xposIn = ev.getX();
            //    float yposIn = ev.getY();
            //    float xpos = static_cast<float>(xposIn);
            //    float ypos = static_cast<float>(yposIn);
            //
            //    if (!lock)
            //    {
            //        lastX = xpos;
            //        lastY = ypos;
            //    }
            //
            //    float xoffset = xpos - lastX;
            //    float yoffset = lastY - ypos;
            //    lastX = xpos;
            //    lastY = ypos;
            //
            //    float sensitivity = 0.1f;
            //    xoffset *= sensitivity;
            //    yoffset *= sensitivity;
            //
            //    yaw += xoffset;
            //    pitch += yoffset;
            //
            //    if (pitch > 89.0f)
            //    {
            //        pitch = 89.0f;
            //    }
            //    if (pitch < -89.0f)
            //    {
            //        pitch = -89.0f;
            //    }
            //    cameraLocation.front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            //    cameraLocation.front.y = sin(glm::radians(pitch));
            //    cameraLocation.front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            //    cameraLocation.front = glm::normalize(cameraLocation.front);
            //}
        }

    private:
        unsigned long index = -1;
        Camera* camera;
    };
}
