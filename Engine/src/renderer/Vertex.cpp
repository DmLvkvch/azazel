#include "Vertex.h"
#include "VertexBuffer.h"

namespace Azazel
{
    BufferLayout Vertex_P3_N3_T2::bufferLayout             { {ShaderDataType::Float3, Semantic::Position3D}, {ShaderDataType::Float3, Semantic::Normal}, {ShaderDataType::Float2, Semantic::Tex_Coord} };

    BufferLayout Vertex_P3_C4_T2::bufferLayout             { {ShaderDataType::Float3, Semantic::Position3D}, {ShaderDataType::Float4, Semantic::Color}, {ShaderDataType::Float2, Semantic::Tex_Coord} };

    BufferLayout Vertex_P3_T2::bufferLayout                { {ShaderDataType::Float3, Semantic::Position3D}, {ShaderDataType::Float2, Semantic::Tex_Coord} };

    BufferLayout Vertex_P3_N3_T2_TAN3_BTAN_3::bufferLayout { {ShaderDataType::Float3, Semantic::Position3D}, 
                                                             {ShaderDataType::Float3, Semantic::Normal}, 
                                                             {ShaderDataType::Float2, Semantic::Tex_Coord},
                                                             {ShaderDataType::Float3, Semantic::Tangent}, 
                                                             {ShaderDataType::Float3, Semantic::Bitangent} };
}