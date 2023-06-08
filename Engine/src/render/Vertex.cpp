#include "Vertex.h"
#include "VertexBuffer.h"

namespace Azazel
{
    BufferLayout Vertex_P3_N3_T2::bufferLayout             { {ShaderDataType::FLOAT3, Semantic::Position3D}, 
                                                             {ShaderDataType::FLOAT3, Semantic::Normal    },
                                                             {ShaderDataType::FLOAT2, Semantic::Tex_Coord }
                                                           };

    BufferLayout Vertex_P3_C4_T2::bufferLayout             { {ShaderDataType::FLOAT3, Semantic::Position3D},
                                                             {ShaderDataType::FLOAT4, Semantic::Color     },
                                                             {ShaderDataType::FLOAT2, Semantic::Tex_Coord }
                                                           };

    BufferLayout Vertex_P3_T2::bufferLayout                { {ShaderDataType::FLOAT3, Semantic::Position3D},
                                                             {ShaderDataType::FLOAT2, Semantic::Tex_Coord }
                                                           };

    BufferLayout Vertex_P3_N3_T2_TAN3_BTAN_3::bufferLayout { {ShaderDataType::FLOAT3, Semantic::Position3D}, 
                                                             {ShaderDataType::FLOAT3, Semantic::Normal    }, 
                                                             {ShaderDataType::FLOAT2, Semantic::Tex_Coord },
                                                             {ShaderDataType::FLOAT3, Semantic::Tangent   }, 
                                                             {ShaderDataType::FLOAT3, Semantic::Bitangent } 
                                                           };
                                                             
    BufferLayout Vertex_P3::bufferLayout                   { {ShaderDataType::FLOAT3, Semantic::Position3D} };
}