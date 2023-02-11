#pragma once

namespace Azazel
{
    class CubeMap
    {
    public:
        CubeMap();
        virtual ~CubeMap();

        virtual void bind() = 0;
        virtual void unbind() = 0;

        static CubeMap* create();
    };
}