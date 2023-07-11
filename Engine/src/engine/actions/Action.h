#pragma once

namespace Azazel
{
    class Action
    {
        virtual bool isDone() const
        {
            return true;
        }

        virtual void stop()
        {

        }

        virtual void step(float dt)
        {

        }

        virtual void update(float time)
        {
            
        }
    }
}