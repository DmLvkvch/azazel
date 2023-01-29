#pragma once

namespace Azazel
{
    static int convertBlendEquation(BlendEquation blendEquation)
    {
        switch (blendEquation)
        {
            case BlendEquation::Add:             return GL_FUNC_ADD;
            case BlendEquation::Subtract:        return GL_FUNC_SUBTRACT;
            case BlendEquation::ReverseSubtract: return GL_FUNC_REVERSE_SUBTRACT;
            case BlendEquation::Max:             return GL_MAX;
            case BlendEquation::Min:             return GL_MIN;
            case BlendEquation::None:            return 0;
        }
        return 0;
    }

    static int convertBlendFunction(BlendFunction blendFunction)
    {
        switch (blendFunction)
        {
            case BlendFunction::Zero:                     return GL_ZERO;
            case BlendFunction::One:                      return GL_ONE;
            case BlendFunction::SrcColor:                 return GL_SRC_COLOR;
            case BlendFunction::OneMinusSrcColor:         return GL_ONE_MINUS_SRC_COLOR;
            case BlendFunction::DstColor:                 return GL_DST_COLOR;
            case BlendFunction::OneMinusDstColor:         return GL_ONE_MINUS_DST_COLOR;
            case BlendFunction::SrcAlpha:                 return GL_SRC_ALPHA;
            case BlendFunction::OneMinusSrcAlpha:         return GL_ONE_MINUS_SRC_ALPHA;
            case BlendFunction::DstAlpha:                 return GL_DST_ALPHA;
            case BlendFunction::OneMinusDstAlpha:         return GL_ONE_MINUS_DST_ALPHA;
            case BlendFunction::ConstantColor:            return GL_CONSTANT_COLOR;
            case BlendFunction::OneMinusConstantColor:    return GL_ONE_MINUS_CONSTANT_COLOR;
            case BlendFunction::ConstantAlpha:            return GL_CONSTANT_ALPHA;
            case BlendFunction::OneMinusConstantAlpha:    return GL_ONE_MINUS_CONSTANT_ALPHA;
            case BlendFunction::SrcAlphaSaturate:         return GL_SRC_ALPHA_SATURATE;
            case BlendFunction::None:                     return 0;
        }
        return 0;
    }

    static int convertCullMode(CullMode cullMode)
    {
        switch (cullMode)
        {
            case CullMode::Front:        return GL_FRONT;
            case CullMode::Back:         return GL_BACK;
            case CullMode::FrontAndBack: return GL_FRONT_AND_BACK;
            case CullMode::None:         return 0;
        }
        return 0;
    }
}