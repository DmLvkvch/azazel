#pragma once

namespace Azazel
{
    class Ref
    {
    public:
        virtual void retain() = 0;
        
        virtual void release() = 0;
        
        Ref* autorelease()
        {

        }

        unsigned int getReferenceCount()
        {
            return referenceCount;
        }
    private:
        unsigned int referenceCount = 0;
    };
}