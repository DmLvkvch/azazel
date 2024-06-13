#pragma once

#include <string>

namespace Azazel
{
    enum class BufferUsage : uint32_t
    {
        STATIC,
        DYNAMIC
    };
    
    enum class ShaderStage : uint32_t
    {
        VERTEX,
        FRAGMENT,
        VERTEX_AND_FRAGMENT
    };

    enum class VertexFormat : uint32_t
    {
        FLOAT4,
        FLOAT3,
        FLOAT2,
        FLOAT,
        INT4,
        INT3,
        INT2,
        INT,
        USHORT4,
        USHORT2,
        UBYTE4
    };

    enum class PixelFormat
    {
        //! auto detect the type
        AUTO,
        //! 32-bit texture: BGRA8888
        BGRA8888,
        //! 32-bit texture: RGBA8888
        RGBA8888,
        //! 24-bit texture: RGBA888
        RGB888,
        //! 16-bit texture without Alpha channel
        RGB565,
        //! 8-bit textures used as masks
        A8,
        //! 8-bit intensity texture
        I8,
        //! 16-bit textures used as masks
        AI88,
        //! 16-bit textures: RGBA4444
        RGBA4444,
        //! 16-bit textures: RGB5A1
        RGB5A1,

        DEFAULT = AUTO,

        NONE = -1
    };

    enum class TextureUsage : uint32_t
    {
        READ,
        WRITE,
        RENDER_TARGET
    };

    enum class IndexFormat : uint32_t
    {
        UNSIGNED_SHORT,
        UNSIGNED_INT
    };

    enum class PrimitiveType : uint32_t
    {
        POINT,
        LINE,
        LINE_STRIP,
        TRIANGLE,
        TRIANGLE_STRIP
    };

    enum class TextureType : uint32_t
    {
        TEXTURE_2D,
        TEXTURE_CUBE
    };

    enum class SamplerAddressMode : uint32_t
    {
        REPEAT,
        MIRROR_REPEAT,
        CLAMP_TO_EDGE,
        DONT_CARE,
    };

    enum class SamplerFilter : uint32_t
    {
        NEAREST,
        NEAREST_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR,
        LINEAR_MIPMAP_LINEAR,
        LINEAR_MIPMAP_NEAREST,
        DONT_CARE,
    };

    enum class StencilOperation : uint32_t
    {
        KEEP,
        ZERO,
        REPLACE,
        INVERT,
        INCREMENT_WRAP,
        DECREMENT_WRAP
    };

    enum class BlendOperation : uint32_t
    {
        ADD,
        SUBTRACT,
        REVERSE_SUBTRACT
    };

    enum class BlendFactor : uint32_t
    {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,
        DST_COLOR,
        ONE_MINUS_DST_COLOR,
        DST_ALPHA,
        ONE_MINUS_DST_ALPHA,
        CONSTANT_ALPHA,
        SRC_ALPHA_SATURATE,
        ONE_MINUS_CONSTANT_ALPHA,
        BLEND_CLOLOR
    };

    enum class ColorWriteMask : uint32_t
    {
        NONE   = 0x00000000,
        RED    = 0x00000001,
        GREEN  = 0x00000002,
        BLUE   = 0x00000004,
        ALPHA  = 0x00000008,
        ALL    = 0x0000000F
    };

    enum class CullMode
    {
        FRONT,
        BACK,
        FRONT_AND_BACK
    };

    enum class CullFront
    {
        CW,
        CCW
    };

    enum class BlendEquation
    {
        ADD,
        SUBTRACT,
        REVERSE_SUBTRACT,
        MIN,
        MAX
    };

    enum class BlendFunction
    {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,
        DST_COLOR,
        ONE_MINUS_DST_COLOR,
        DST_ALPHA,
        ONE_MINUS_DST_ALPHA,
        CONSTANT_ALPHA,
        SRC_ALPHA_SATURATE,
        ONE_MINUS_CONSTANT_ALPHA,
        CONSTANT_COLOR,
        ONE_MINUS_CONSTANT_COLOR
    };

    enum class CompareFunction : uint32_t
    {
        NEVER,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
        EQUAL,
        NOT_EQUAL,
        ALWAYS
    };

    enum class StencilFunc
    {
        KEEP,
        ZERO,
        REPLACE,
        INCR,
        INCR_WRAP,
        DECR,
        DECR_WRAP,
        INVERT
    };

    struct SamplerDescriptor
    {
        SamplerFilter magFilter = SamplerFilter::LINEAR;
        SamplerFilter minFilter = SamplerFilter::LINEAR;
        SamplerAddressMode sAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;
        SamplerAddressMode tAddressMode = SamplerAddressMode::CLAMP_TO_EDGE;

        SamplerDescriptor() {}

        SamplerDescriptor(
            SamplerFilter _magFilter,
            SamplerFilter _minFilter,
            SamplerAddressMode _sAddressMode,
            SamplerAddressMode _tAddressMode
        ) : magFilter(_magFilter), minFilter(_minFilter),
            sAddressMode(_sAddressMode), tAddressMode(_tAddressMode) {}
    };

    enum class Winding : uint32_t
    {
        CLOCK_WISE,
        COUNTER_CLOCK_WISE
    };

    struct UniformInfo
    {
        int count = 0;
        int location = -1;

        unsigned int type = 0;
        bool isArray = false;
        unsigned int size = 0;
        unsigned int bufferOffset = 0;

        bool isMatrix = false;
        bool needConvert = false;
    };

    struct AttributeBindInfo
    {
        std::string attributeName;
        int         location = -1;
        int         size = 0;
        int         type = 0;
    };

    enum class TextureCubeFace : uint32_t
    {
        POSITIVE_X = 0,
        NEGATIVE_X = 1,
        POSITIVE_Y = 2,
        NEGATIVE_Y = 3,
        POSITIVE_Z = 4,
        NEGATIVE_Z = 5
    };

    struct BlendDescriptor
    {
        ColorWriteMask writeMask = ColorWriteMask::ALL;

        bool blendEnabled = false;

        BlendOperation rgbBlendOperation = BlendOperation::ADD;
        BlendOperation alphaBlendOperation = BlendOperation::ADD;

        BlendFactor sourceRGBBlendFactor = BlendFactor::ONE;
        BlendFactor destinationRGBBlendFactor = BlendFactor::ZERO;
        BlendFactor sourceAlphaBlendFactor = BlendFactor::ONE;
        BlendFactor destinationAlphaBlendFactor = BlendFactor::ZERO;
    };
}