#pragma once

#include "render/Types.h"
#include "render/rhi/gl/gl_headers.h"

namespace Azazel
{
    static int convertBlendEquation(BlendEquation blendEquation)
    {
        switch (blendEquation)
        {
            case BlendEquation::ADD:              return GL_FUNC_ADD;
            case BlendEquation::SUBTRACT:         return GL_FUNC_SUBTRACT;
            case BlendEquation::REVERSE_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT;
            case BlendEquation::MAX:              return GL_MAX;
            case BlendEquation::MIN:              return GL_MIN;
        }
        return 0;
    }

    static int convertBlendFunction(BlendFunction blendFunction)
    {
        switch (blendFunction)
        {
            case BlendFunction::ZERO:                        return GL_ZERO;
            case BlendFunction::ONE:                         return GL_ONE;
            case BlendFunction::SRC_COLOR:                   return GL_SRC_COLOR;
            case BlendFunction::ONE_MINUS_SRC_COLOR:         return GL_ONE_MINUS_SRC_COLOR;
            case BlendFunction::DST_COLOR:                   return GL_DST_COLOR;
            case BlendFunction::ONE_MINUS_DST_COLOR:         return GL_ONE_MINUS_DST_COLOR;
            case BlendFunction::SRC_ALPHA:                   return GL_SRC_ALPHA;
            case BlendFunction::ONE_MINUS_SRC_ALPHA:         return GL_ONE_MINUS_SRC_ALPHA;
            case BlendFunction::DST_ALPHA:                   return GL_DST_ALPHA;
            case BlendFunction::ONE_MINUS_DST_ALPHA:         return GL_ONE_MINUS_DST_ALPHA;
            case BlendFunction::CONSTANT_COLOR:              return GL_CONSTANT_COLOR;
            case BlendFunction::ONE_MINUS_CONSTANT_COLOR:    return GL_ONE_MINUS_CONSTANT_COLOR;
            case BlendFunction::CONSTANT_ALPHA:              return GL_CONSTANT_ALPHA;
            case BlendFunction::ONE_MINUS_CONSTANT_ALPHA:    return GL_ONE_MINUS_CONSTANT_ALPHA;
            case BlendFunction::SRC_ALPHA_SATURATE:          return GL_SRC_ALPHA_SATURATE;
        }
        return 0;
    }

    static int convertCullMode(CullMode cullMode)
    {
        switch (cullMode)
        {
            case CullMode::FRONT:          return GL_FRONT;
            case CullMode::BACK:           return GL_BACK;
            case CullMode::FRONT_AND_BACK: return GL_FRONT_AND_BACK;
        }
        return 0;
    }

    static int convertCullFront(CullFront cullFront)
    {
        switch (cullFront)
        {
            case CullFront::CCW: return GL_CCW;
            case CullFront::CW:  return GL_CW;
        }
        return 0;
    }

    static unsigned int convertCompareFunction(CompareFunction compareFunction)
    {
        switch (compareFunction)
        {
            case CompareFunction::NEVER:         return GL_NEVER;
            case CompareFunction::LESS:          return GL_LESS;
            case CompareFunction::LESS_EQUAL:    return GL_LEQUAL;
            case CompareFunction::GREATER:       return GL_GREATER;
            case CompareFunction::GREATER_EQUAL: return GL_GEQUAL;
            case CompareFunction::NOT_EQUAL:     return GL_NOTEQUAL;
            case CompareFunction::EQUAL:         return GL_EQUAL;
            case CompareFunction::ALWAYS:        return GL_ALWAYS;
        }
        return 0;
    }

    static unsigned int convertStencilOp(StencilOperation stencilOp)
    {
        switch (stencilOp)
        {
            case StencilOperation::KEEP:           return GL_KEEP;
            case StencilOperation::ZERO:           return GL_ZERO;
            case StencilOperation::REPLACE:        return GL_REPLACE;
            case StencilOperation::INVERT:         return GL_INVERT;
            case StencilOperation::INCREMENT_WRAP: return GL_INCR_WRAP;
            case StencilOperation::DECREMENT_WRAP: return GL_DECR_WRAP;
        }
        return 0;
    }
}