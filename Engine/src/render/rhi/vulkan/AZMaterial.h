#pragma once

#include "VectorMath.h"

#include <ShaderLang.h>
#include <GlslangToSpv.h>
#include <spirv_reflect.h>

#include <fstream>

namespace vk
{
    enum class Format;
    enum class DescriptorType;
    enum class ShaderStageFlagBits : uint32_t;
    enum class ImageLayout;
}

namespace Azazel
{
    EShLanguage ShaderTypeTable[] = {
        EShLangVertex,
        EShLangTessControl,
        EShLangTessEvaluation,
        EShLangGeometry,
        EShLangFragment,
        EShLangCompute,
        EShLangRayGen,
        EShLangIntersect,
        EShLangAnyHit,
        EShLangClosestHit,
        EShLangMiss,
        EShLangCallable,
        EShLangTaskNV,
        EShLangMeshNV,
    };

    glslang::EShSource ShaderLanguageTable[] = {
        glslang::EShSource::EShSourceGlsl,
        glslang::EShSource::EShSourceHlsl,
    };

    constexpr auto GetResourceLimits()
    {
        TBuiltInResource defaultResources = {};
        defaultResources.maxLights = 32;
        defaultResources.maxClipPlanes = 6;
        defaultResources.maxTextureUnits = 32;
        defaultResources.maxTextureCoords = 32;
        defaultResources.maxVertexAttribs = 64;
        defaultResources.maxVertexUniformComponents = 4096;
        defaultResources.maxVaryingFloats = 64;
        defaultResources.maxVertexTextureImageUnits = 32;
        defaultResources.maxCombinedTextureImageUnits = 80;
        defaultResources.maxTextureImageUnits = 32;
        defaultResources.maxFragmentUniformComponents = 4096;
        defaultResources.maxDrawBuffers = 32;
        defaultResources.maxVertexUniformVectors = 128;
        defaultResources.maxVaryingVectors = 8;
        defaultResources.maxFragmentUniformVectors = 16;
        defaultResources.maxVertexOutputVectors = 16;
        defaultResources.maxFragmentInputVectors = 15;
        defaultResources.minProgramTexelOffset = -8;
        defaultResources.maxProgramTexelOffset = 7;
        defaultResources.maxClipDistances = 8;
        defaultResources.maxComputeWorkGroupCountX = 65535;
        defaultResources.maxComputeWorkGroupCountY = 65535;
        defaultResources.maxComputeWorkGroupCountZ = 65535;
        defaultResources.maxComputeWorkGroupSizeX = 1024;
        defaultResources.maxComputeWorkGroupSizeY = 1024;
        defaultResources.maxComputeWorkGroupSizeZ = 64;
        defaultResources.maxComputeUniformComponents = 1024;
        defaultResources.maxComputeTextureImageUnits = 16;
        defaultResources.maxComputeImageUniforms = 8;
        defaultResources.maxComputeAtomicCounters = 8;
        defaultResources.maxComputeAtomicCounterBuffers = 1;
        defaultResources.maxVaryingComponents = 60;
        defaultResources.maxVertexOutputComponents = 64;
        defaultResources.maxGeometryInputComponents = 64;
        defaultResources.maxGeometryOutputComponents = 128;
        defaultResources.maxFragmentInputComponents = 128;
        defaultResources.maxImageUnits = 8;
        defaultResources.maxCombinedImageUnitsAndFragmentOutputs = 8;
        defaultResources.maxCombinedShaderOutputResources = 8;
        defaultResources.maxImageSamples = 0;
        defaultResources.maxVertexImageUniforms = 0;
        defaultResources.maxTessControlImageUniforms = 0;
        defaultResources.maxTessEvaluationImageUniforms = 0;
        defaultResources.maxGeometryImageUniforms = 0;
        defaultResources.maxFragmentImageUniforms = 8;
        defaultResources.maxCombinedImageUniforms = 8;
        defaultResources.maxGeometryTextureImageUnits = 16;
        defaultResources.maxGeometryOutputVertices = 256;
        defaultResources.maxGeometryTotalOutputComponents = 1024;
        defaultResources.maxGeometryUniformComponents = 1024;
        defaultResources.maxGeometryVaryingComponents = 64;
        defaultResources.maxTessControlInputComponents = 128;
        defaultResources.maxTessControlOutputComponents = 128;
        defaultResources.maxTessControlTextureImageUnits = 16;
        defaultResources.maxTessControlUniformComponents = 1024;
        defaultResources.maxTessControlTotalOutputComponents = 4096;
        defaultResources.maxTessEvaluationInputComponents = 128;
        defaultResources.maxTessEvaluationOutputComponents = 128;
        defaultResources.maxTessEvaluationTextureImageUnits = 16;
        defaultResources.maxTessEvaluationUniformComponents = 1024;
        defaultResources.maxTessPatchComponents = 120;
        defaultResources.maxPatchVertices = 32;
        defaultResources.maxTessGenLevel = 64;
        defaultResources.maxViewports = 16;
        defaultResources.maxVertexAtomicCounters = 0;
        defaultResources.maxTessControlAtomicCounters = 0;
        defaultResources.maxTessEvaluationAtomicCounters = 0;
        defaultResources.maxGeometryAtomicCounters = 0;
        defaultResources.maxFragmentAtomicCounters = 8;
        defaultResources.maxCombinedAtomicCounters = 8;
        defaultResources.maxAtomicCounterBindings = 1;
        defaultResources.maxVertexAtomicCounterBuffers = 0;
        defaultResources.maxTessControlAtomicCounterBuffers = 0;
        defaultResources.maxTessEvaluationAtomicCounterBuffers = 0;
        defaultResources.maxGeometryAtomicCounterBuffers = 0;
        defaultResources.maxFragmentAtomicCounterBuffers = 1;
        defaultResources.maxCombinedAtomicCounterBuffers = 1;
        defaultResources.maxAtomicCounterBufferSize = 16384;
        defaultResources.maxTransformFeedbackBuffers = 4;
        defaultResources.maxTransformFeedbackInterleavedComponents = 64;
        defaultResources.maxCullDistances = 8;
        defaultResources.maxCombinedClipAndCullDistances = 8;
        defaultResources.maxSamples = 4;
        defaultResources.maxMeshOutputVerticesNV = 256;
        defaultResources.maxMeshOutputPrimitivesNV = 512;
        defaultResources.maxMeshWorkGroupSizeX_NV = 32;
        defaultResources.maxMeshWorkGroupSizeY_NV = 1;
        defaultResources.maxMeshWorkGroupSizeZ_NV = 1;
        defaultResources.maxTaskWorkGroupSizeX_NV = 32;
        defaultResources.maxTaskWorkGroupSizeY_NV = 1;
        defaultResources.maxTaskWorkGroupSizeZ_NV = 1;
        defaultResources.maxMeshViewCountNV = 4;
        defaultResources.maxDualSourceDrawBuffersEXT = 1;
        defaultResources.limits.nonInductiveForLoops = 1;
        defaultResources.limits.whileLoops = 1;
        defaultResources.limits.doWhileLoops = 1;
        defaultResources.limits.generalUniformIndexing = 1;
        defaultResources.limits.generalAttributeMatrixVectorIndexing = 1;
        defaultResources.limits.generalVaryingIndexing = 1;
        defaultResources.limits.generalSamplerIndexing = 1;
        defaultResources.limits.generalVariableIndexing = 1;
        defaultResources.limits.generalConstantMatrixVectorIndexing = 1;
        
        return defaultResources;
    }

    enum class ShaderType : uint32_t
    {
        VERTEX = 0,
        TESS_CONTROL,
        TESS_EVALUATION,
        GEOMETRY,
        FRAGMENT,
        COMPUTE,
        RAY_GEN,
        INTERSECT,
        ANY_HIT,
        CLOSEST_HIT,
        MISS,
        CALLABLE,
        TASK_NV,
        MESH_NV,
    };

    const vk::ShaderStageFlagBits& ToNative(ShaderType type);
    ShaderType FromNative(const vk::ShaderStageFlagBits& type);

    enum class ShaderLanguage
    {
        GLSL = 0,
        HLSL,
    };

    enum class Format : uint32_t
    {
        UNDEFINED = 0,
        R4G4_UNORM_PACK_8,
        R4G4B4A4_UNORM_PACK_16,
        B4G4R4A4_UNORM_PACK_16,
        R5G6B5_UNORM_PACK_16,
        B5G6R5_UNORM_PACK_16,
        R5G5B5A1_UNORM_PACK_16,
        B5G5R5A1_UNORM_PACK_16,
        A1R5G5B5_UNORM_PACK_16,
        R8_UNORM,
        R8_SNORM,
        R8_USCALED,
        R8_SSCALED,
        R8_UINT,
        R8_SINT,
        R8_SRGB,
        R8G8_UNORM,
        R8G8_SNORM,
        R8G8_USCALED,
        R8G8_SSCALED,
        R8G8_UINT,
        R8G8_SINT,
        R8G8_SRGB,
        R8G8B8_UNORM,
        R8G8B8_SNORM,
        R8G8B8_USCALED,
        R8G8B8_SSCALED,
        R8G8B8_UINT,
        R8G8B8_SINT,
        R8G8B8_SRGB,
        B8G8R8_UNORM,
        B8G8R8_SNORM,
        B8G8R8_USCALED,
        B8G8R8_SSCALED,
        B8G8R8_UINT,
        B8G8R8_SINT,
        B8G8R8_SRGB,
        R8G8B8A8_UNORM,
        R8G8B8A8_SNORM,
        R8G8B8A8_USCALED,
        R8G8B8A8_SSCALED,
        R8G8B8A8_UINT,
        R8G8B8A8_SINT,
        R8G8B8A8_SRGB,
        B8G8R8A8_UNORM,
        B8G8R8A8_SNORM,
        B8G8R8A8_USCALED,
        B8G8R8A8_SSCALED,
        B8G8R8A8_UINT,
        B8G8R8A8_SINT,
        B8G8R8A8_SRGB,
        A8B8G8R8_UNORM_PACK_32,
        A8B8G8R8_SNORM_PACK_32,
        A8B8G8R8_USCALED_PACK_32,
        A8B8G8R8_SSCALED_PACK_32,
        A8B8G8R8_UINT_PACK_32,
        A8B8G8R8_SINT_PACK_32,
        A8B8G8R8_SRGB_PACK_32,
        A2R10G10B10_UNORM_PACK_32,
        A2R10G10B10_SNORM_PACK_32,
        A2R10G10B10_USCALED_PACK_32,
        A2R10G10B10_SSCALED_PACK_32,
        A2R10G10B10_UINT_PACK_32,
        A2R10G10B10_SINT_PACK_32,
        A2B10G10R10_UNORM_PACK_32,
        A2B10G10R10_SNORM_PACK_32,
        A2B10G10R10_USCALED_PACK_32,
        A2B10G10R10_SSCALED_PACK_32,
        A2B10G10R10_UINT_PACK_32,
        A2B10G10R10_SINT_PACK_32,
        R16_UNORM,
        R16_SNORM,
        R16_USCALED,
        R16_SSCALED,
        R16_UINT,
        R16_SINT,
        R16_SFLOAT,
        R16G16_UNORM,
        R16G16_SNORM,
        R16G16_USCALED,
        R16G16_SSCALED,
        R16G16_UINT,
        R16G16_SINT,
        R16G16_SFLOAT,
        R16G16B16_UNORM,
        R16G16B16_SNORM,
        R16G16B16_USCALED,
        R16G16B16_SSCALED,
        R16G16B16_UINT,
        R16G16B16_SINT,
        R16G16B16_SFLOAT,
        R16G16B16A16_UNORM,
        R16G16B16A16_SNORM,
        R16G16B16A16_USCALED,
        R16G16B16A16_SSCALED,
        R16G16B16A16_UINT,
        R16G16B16A16_SINT,
        R16G16B16A16_SFLOAT,
        R32_UINT,
        R32_SINT,
        R32_SFLOAT,
        R32G32_UINT,
        R32G32_SINT,
        R32G32_SFLOAT,
        R32G32B32_UINT,
        R32G32B32_SINT,
        R32G32B32_SFLOAT,
        R32G32B32A32_UINT,
        R32G32B32A32_SINT,
        R32G32B32A32_SFLOAT,
        R64_UINT,
        R64_SINT,
        R64_SFLOAT,
        R64G64_UINT,
        R64G64_SINT,
        R64G64_SFLOAT,
        R64G64B64_UINT,
        R64G64B64_SINT,
        R64G64B64_SFLOAT,
        R64G64B64A64_UINT,
        R64G64B64A64_SINT,
        R64G64B64A64_SFLOAT,
        B10G11R11_UFLOAT_PACK_32,
        E5B9G9R9_UFLOAT_PACK_32,
        D16_UNORM,
        X8D24_UNORM_PACK_32,
        D32_SFLOAT,
        S8_UINT,
        D16_UNORM_S8_UINT,
        D24_UNORM_S8_UINT,
        D32_SFLOAT_S8_UINT,
    };

    const vk::Format& ToNative(Format format);
    Format FromNative(const vk::Format& format);

    enum class UniformType : uint32_t
    {
        SAMPLER = 0,
        COMBINED_IMAGE_SAMPLER,
        SAMPLED_IMAGE,
        STORAGE_IMAGE,
        UNIFORM_TEXEL_BUFFER,
        STORAGE_TEXEL_BUFFER,
        UNIFORM_BUFFER,
        STORAGE_BUFFER,
        UNIFORM_BUFFER_DYNAMIC,
        STORAGE_BUFFER_DYNAMIC,
        INPUT_ATTACHMENT,
        INLINE_UNIFORM_BLOCK_EXT,
        ACCELERATION_STRUCTURE_KHR,
    };

    const vk::DescriptorType& ToNative(UniformType type);
    UniformType FromNative(const vk::DescriptorType& type);

    struct TypeSPIRV
    {
        Format LayoutFormat;
        int32_t ComponentCount;
        int32_t ByteSize;

        template<typename T>
        static TypeSPIRV As();
    };

    struct VertexBinding
    {
        enum class Rate : uint8_t
        {
            PER_VERTEX = 0,
            PER_INSTANCE
        } InputRate;

        uint32_t BindingRange;

        constexpr static uint32_t BindingRangeAll = uint32_t(-1);
    };

    struct Uniform
    {
        std::vector<TypeSPIRV> Layout;
        UniformType Type;
        uint32_t Binding;
        uint32_t Count;
    };

    struct ShaderUniforms
    {
        std::vector<Uniform> Uniforms;
        ShaderType ShaderStage;
    };

    inline bool operator==(const TypeSPIRV& t1, const TypeSPIRV& t2) { return t1.LayoutFormat == t2.LayoutFormat && t1.ComponentCount == t2.ComponentCount && t1.ByteSize == t2.ByteSize; }
    inline bool operator!=(const TypeSPIRV& t1, const TypeSPIRV& t2) { return !(t1 == t2); }

    inline bool operator==(const Uniform& u1, const Uniform& u2) { return u1.Layout == u2.Layout && u1.Type == u2.Type && u1.Binding == u2.Binding && u1.Count == u2.Count; }
    inline bool operator!=(const Uniform& u1, const Uniform& u2) { return !(u1 == u2); }

    inline bool operator==(const ShaderUniforms& u1, const ShaderUniforms& u2) { return u1.ShaderStage == u2.ShaderStage && u1.Uniforms == u2.Uniforms; }
    inline bool operator!=(const ShaderUniforms& u1, const ShaderUniforms& u2) { return !(u1 == u2); }

    TypeSPIRV GetTypeByReflection(const SpvReflectTypeDescription& type)
    {
        Format format = Format::UNDEFINED;
        if (type.type_flags & SPV_REFLECT_TYPE_FLAG_FLOAT)
        {
            if (type.traits.numeric.vector.component_count <  2 || type.traits.numeric.matrix.column_count <  2)
                format = Format::R32_SFLOAT;
            if (type.traits.numeric.vector.component_count == 2 || type.traits.numeric.matrix.column_count == 2)
                format = Format::R32G32_SFLOAT;
            if (type.traits.numeric.vector.component_count == 3 || type.traits.numeric.matrix.column_count == 3)
                format = Format::R32G32B32_SFLOAT;
            if (type.traits.numeric.vector.component_count == 4 || type.traits.numeric.matrix.column_count == 4)
                format = Format::R32G32B32A32_SFLOAT;
        }
        if (type.type_flags & SPV_REFLECT_TYPE_FLAG_INT)
        {
            if (type.traits.numeric.vector.component_count <  2 || type.traits.numeric.matrix.column_count <  2)
                format = type.traits.numeric.scalar.signedness ? Format::R32_SINT : Format::R32_UINT;
            if (type.traits.numeric.vector.component_count == 2 || type.traits.numeric.matrix.column_count == 2)
                format = type.traits.numeric.scalar.signedness ? Format::R32G32_SINT : Format::R32G32_UINT;
            if (type.traits.numeric.vector.component_count == 3 || type.traits.numeric.matrix.column_count == 3)
                format = type.traits.numeric.scalar.signedness ? Format::R32G32B32_SINT : Format::R32G32B32_UINT;
            if (type.traits.numeric.vector.component_count == 4 || type.traits.numeric.matrix.column_count == 4)
                format = type.traits.numeric.scalar.signedness ? Format::R32G32B32A32_SINT : Format::R32G32B32A32_UINT;
        }
        if (type.type_flags & SPV_REFLECT_TYPE_FLAG_ARRAY)
        {
            if (type.traits.numeric.vector.component_count < 2 || type.traits.numeric.matrix.column_count < 2)
                format = Format::R32_SFLOAT;
            if (type.traits.numeric.vector.component_count == 2 || type.traits.numeric.matrix.column_count == 2)
                format = Format::R32G32_SFLOAT;
            if (type.traits.numeric.vector.component_count == 3 || type.traits.numeric.matrix.column_count == 3)
                format = Format::R32G32B32_SFLOAT;
            if (type.traits.numeric.vector.component_count == 4 || type.traits.numeric.matrix.column_count == 4)
                format = Format::R32G32B32A32_SFLOAT;
        }
        assert(format != Format::UNDEFINED);

        int32_t byteSize = type.traits.numeric.scalar.width / 8;
        int32_t componentCount = 1;

        if (type.traits.numeric.vector.component_count > 0)
            byteSize *= type.traits.numeric.vector.component_count;
        else if (type.traits.numeric.matrix.row_count > 0)
            byteSize *= type.traits.numeric.matrix.row_count;

        if (type.traits.numeric.matrix.column_count > 0)
            componentCount = type.traits.numeric.matrix.column_count;

        return TypeSPIRV{ format, componentCount, byteSize };
    }

    void RecursiveUniformVisit(std::vector<TypeSPIRV>& uniformVariables, const SpvReflectTypeDescription& type)
    {
        if (type.member_count > 0)
        {
            for (uint32_t i = 0; i < type.member_count; i++)
                RecursiveUniformVisit(uniformVariables, type.members[i]);
        }
        else
        {
            if(type.type_flags & (SPV_REFLECT_TYPE_FLAG_INT | SPV_REFLECT_TYPE_FLAG_FLOAT))
                uniformVariables.push_back(GetTypeByReflection(type));
        }
    }

    struct ShaderData
    {
        using BytecodeSPIRV = std::vector<uint32_t>;
        using Attributes = std::vector<TypeSPIRV>;
        using UniformBlock = std::vector<Uniform>;
        using Uniforms = std::vector<UniformBlock>;

        BytecodeSPIRV Bytecode;
        Attributes InputAttributes;
        Uniforms DescriptorSets;
    };

    static ShaderData LoadFromSourceFile(const std::string& filepath, ShaderType type, ShaderLanguage language);
    static ShaderData LoadFromBinaryFile(const std::string& filepath);

    static ShaderData LoadFromSource(const std::string& code, ShaderType type, ShaderLanguage language);
    static ShaderData LoadFromBinary(std::vector<uint32_t> bytecode);

    ShaderData LoadFromBinaryFile(const std::string& filepath)
    {
        std::vector<uint32_t> bytecode;
        std::ifstream file(filepath, std::ios_base::binary);
        auto binaryData = std::vector<char>(std::istreambuf_iterator(file), std::istreambuf_iterator<char>());
        bytecode.resize(binaryData.size() / sizeof(uint32_t));
        std::copy((uint32_t*)binaryData.data(), (uint32_t*)(binaryData.data() + binaryData.size()), bytecode.begin());
        return LoadFromBinary(std::move(bytecode));
    }

    ShaderData LoadFromSourceFile(const std::string& filepath, ShaderType type, ShaderLanguage language)
    {
        std::ifstream file(filepath);
        std::string source{ std::istreambuf_iterator(file), std::istreambuf_iterator<char>() };
        return LoadFromSource(source, type, language);
    }

    ShaderData LoadFromSource(const std::string& code, ShaderType type, ShaderLanguage language)
    {
        const char* rawSource = code.c_str();
        constexpr static auto ResourceLimits = GetResourceLimits();

        glslang::TShader shader{ ShaderTypeTable[(size_t)type] };
        shader.setStrings(&rawSource, 1);
        shader.setEnvInput(ShaderLanguageTable[(size_t)language], ShaderTypeTable[(size_t)type], glslang::EShClient::EShClientVulkan, 460);
        shader.setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_3);
        shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetSpv_1_5);
        bool isParsed = shader.parse(&ResourceLimits, 460, false, EShMessages::EShMsgDefault);
        if (!isParsed) return ShaderData{ };

        glslang::TProgram program;
        program.addShader(&shader);
        bool isLinked = program.link(EShMessages::EShMsgDefault);
        if (!isLinked) return ShaderData{ };

        auto intermediate = program.getIntermediate(ShaderTypeTable[(size_t)type]);
        std::vector<uint32_t> bytecode;
        glslang::GlslangToSpv(*intermediate, bytecode);

        return LoadFromBinary(std::move(bytecode));
    }

    ShaderData LoadFromBinary(std::vector<uint32_t> bytecode)
    {
        ShaderData result;
        result.Bytecode = std::move(bytecode);

        SpvReflectResult spvResult;
        SpvReflectShaderModule reflectedShader;
        spvResult = spvReflectCreateShaderModule(result.Bytecode.size() * sizeof(uint32_t), (const void*)result.Bytecode.data(), &reflectedShader);
        assert(spvResult == SPV_REFLECT_RESULT_SUCCESS);

        uint32_t inputAttributeCount = 0;
        spvResult = spvReflectEnumerateInputVariables(&reflectedShader, &inputAttributeCount, nullptr);
        assert(spvResult == SPV_REFLECT_RESULT_SUCCESS);
        std::vector<SpvReflectInterfaceVariable*> inputAttributes(inputAttributeCount);
        spvResult = spvReflectEnumerateInputVariables(&reflectedShader, &inputAttributeCount, inputAttributes.data());
        assert(spvResult == SPV_REFLECT_RESULT_SUCCESS);

        // sort in location order
        std::sort(inputAttributes.begin(), inputAttributes.end(), [](const auto& v1, const auto& v2) { return v1->location < v2->location; });
        for (const auto& inputAttribute : inputAttributes)
        {
            if (inputAttribute->built_in == (SpvBuiltIn)-1) // ignore build-ins
            {
                result.InputAttributes.push_back(GetTypeByReflection(*inputAttribute->type_description));
            }
        }

        uint32_t descriptorBindingCount = 0;
        spvResult = spvReflectEnumerateDescriptorBindings(&reflectedShader, &descriptorBindingCount, nullptr);
        assert(spvResult == SPV_REFLECT_RESULT_SUCCESS);
        std::vector<SpvReflectDescriptorBinding*> descriptorBindings(descriptorBindingCount);
        spvResult = spvReflectEnumerateDescriptorBindings(&reflectedShader, &descriptorBindingCount, descriptorBindings.data());
        assert(spvResult == SPV_REFLECT_RESULT_SUCCESS);

        for (const auto& descriptorBinding : descriptorBindings)
        {
            if (result.DescriptorSets.size() < (size_t)descriptorBinding->set + 1)
                result.DescriptorSets.resize((size_t)descriptorBinding->set + 1);

            auto& uniformBlock = result.DescriptorSets[descriptorBinding->set];

            std::vector<TypeSPIRV> uniformVariables;
            RecursiveUniformVisit(uniformVariables, *descriptorBinding->type_description);

            uniformBlock.push_back(Uniform { 
                std::move(uniformVariables),
                FromNative((vk::DescriptorType)descriptorBinding->descriptor_type),
                descriptorBinding->binding,
                descriptorBinding->count
            });
        }
        if (result.DescriptorSets.empty()) 
            result.DescriptorSets.emplace_back(); // insert empty descriptor set

        spvReflectDestroyShaderModule(&reflectedShader);

        return result;
    }

    class AZShader
    {

    };

    class AZMaterial
    {

    };
}