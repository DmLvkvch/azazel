#pragma once

namespace Azazel
{
    class UpdateTarget
    {
        virtual void update(float delta) = 0;
    };
}