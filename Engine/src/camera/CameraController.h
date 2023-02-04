#pragma once

#include "OrthographicCamera.h"

namespace Azazel
{
    class CameraController
    {
        CameraController();
        ~CameraController();
        void onUpdate(float delta);
    private:
        OrthographicCamera camera;
    };
}