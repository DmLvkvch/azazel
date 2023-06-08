#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "events/Event.h"
#include "events/KeyEvent.h"
#include "events/MouseEvent.h"
#include "events/ApplicationEvent.h"
#include "IO/Input.h"
#include "IO/KeyCodes.h"

#include <iostream>

namespace Azazel
{
    struct CameraProjection
    {
        float fov = 45.0f;
        float width = 1280.0f;
        float height = 720.0f;
        float near = 0.1f;
        float far = 100.0f;

        glm::mat4 getProjectionMatrix()
        {
            return glm::perspective(glm::radians(fov), width / height, near, far);
        }
    };

    struct CameraLocation
    {
        glm::vec3 position { 0.0f, 0.0f, 0.0f };
        glm::vec3 up { 0.0f, 1.0f, 0.0f };
        glm::vec3 front {0.0f, 0.0f, -1.0f};
    };

    class Camera
    {
    public:

        Camera()
        {
            std::cout << "Camera constructor" << std::endl;
        }

        ~Camera()
        {
            std::cout << "Camera destructor" << std::endl;
        }

        void onInputUpdate(float delta)
        {
            float cameraSpeed = static_cast<float>(2.5 * delta) / 1000.0f;
            if (Input::getInput()->isKeyPressed(KEY_W))
            {
                moveForward(cameraSpeed);
            }
            if (Input::getInput()->isKeyPressed(KEY_S))
            {
                moveForward(-cameraSpeed);
            }
            if (Input::getInput()->isKeyPressed(KEY_A))
            {
                moveRight(cameraSpeed);
            }
            if (Input::getInput()->isKeyPressed(KEY_D))
            {
                moveRight(-cameraSpeed);
            }
            if (Input::getInput()->isKeyPressed(KEY_Q))
            {
                moveUp(cameraSpeed);
            }
            if (Input::getInput()->isKeyPressed(KEY_E))
            {
                moveUp(-cameraSpeed);
            }
        }

        const glm::vec3& getViewDirection() const
        {
            return cameraLocation.front;
        }

        const glm::vec3& getViewPosition() const
        {
            return cameraLocation.position;
        }

        void setPosition(const glm::vec3& position);

        void setDirection(const glm::vec3& direction);

        void moveForward(float z)
        {
            cameraLocation.position += z * cameraLocation.front;
        }

        void moveRight(float z)
        {
            cameraLocation.position -= glm::normalize(glm::cross(cameraLocation.front, cameraLocation.up)) * z;
        }

        void moveUp(float z)
        {
            cameraLocation.position -= cameraLocation.up * z;
        }

        void setLookAtPosition(const glm::vec3& lookAtPosition = glm::vec3(0.0f, 0.0f, 0.0f));

        glm::mat4 getViewLookAtMatrix(glm::vec3 lookAtPosition);

        glm::mat4 getViewLookAtMatrix()
        {
            return glm::mat4(1.0f);
        }

        glm::mat4 getViewMatrix();

        inline const glm::vec3& getImmutablePosition() const
        {
            return cameraLocation.position;
        }

        glm::mat4 getProjectionMatrix()
        {
            return cameraProjection.getProjectionMatrix();
        }

        glm::mat4 getViewProjectionMatrix()
        {
            return getProjectionMatrix() * getViewMatrix();
        }

        void move(const glm::vec3& move);

        void zoomCamera(float offset)
        {
            cameraProjection.fov -= offset;
            if (cameraProjection.fov < 1.0f)
            {
                cameraProjection.fov = 1.0f;
            }
            if (cameraProjection.fov > 45.0f)
            {
                cameraProjection.fov = 45.0f;
            }
        }

        void onEvent(Event& e)
        {
            if (e.getEventType() == EventType::MouseScrolled)
            {
                const MouseScrollEvent& ev = *(MouseScrollEvent*)(&e);
                zoomCamera(ev.getY());
            }
            if (e.getEventType() == EventType::MousePressed)
            {
                lock = true;
            }
            if (e.getEventType() == EventType::MouseReleased)
            {
                lock = false;
            }
            if (e.getEventType() == EventType::MouseMoved)
            {
                const MouseMovedEvent& ev = *(MouseMovedEvent*)(&e);
                float xposIn = ev.getX();
                float yposIn = ev.getY();
                float xpos = static_cast<float>(xposIn);
                float ypos = static_cast<float>(yposIn);

                if (!lock)
                {
                    lastX = xpos;
                    lastY = ypos;
                }

                float xoffset = xpos - lastX;
                float yoffset = lastY - ypos;
                lastX = xpos;
                lastY = ypos;

                float sensitivity = 0.1f;
                xoffset *= sensitivity;
                yoffset *= sensitivity;

                yaw += xoffset;
                pitch += yoffset;

                if (pitch > 89.0f)
                {
                    pitch = 89.0f;
                }
                if (pitch < -89.0f)
                {
                    pitch = -89.0f;
                }
                cameraLocation.front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                cameraLocation.front.y = sin(glm::radians(pitch));
                cameraLocation.front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                cameraLocation.front = glm::normalize(cameraLocation.front);
            }
        }
    private:
        void updateCamera();

    public:
        float yaw = -90.0f;
        float pitch = 0.0f;
        float lastX = 1280.0f / 2.0f;
        float lastY = 720.0f / 2.0f;
        
        size_t index = -1;
        bool lock = false;
        
        CameraLocation cameraLocation;

        CameraProjection cameraProjection;
    };
}