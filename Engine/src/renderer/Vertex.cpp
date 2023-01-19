#include "Vertex.h"
#include "VertexBuffer.h"

namespace Azazel
{
    BufferLayout Vertex_P3_N3_T2::bufferLayout             { {ShaderDataType::Float3, "pos"}, {ShaderDataType::Float3, "norm"}, {ShaderDataType::Float2, "tex_coord"} };

    BufferLayout Vertex_P3_C4_T2::bufferLayout             { {ShaderDataType::Float3, "pos"}, {ShaderDataType::Float4, "col"}, {ShaderDataType::Float2, "tex_coord"} };

    BufferLayout Vertex_P3_T2::bufferLayout                { {ShaderDataType::Float3, "pos"}, {ShaderDataType::Float2, "tex_coord"} };

    BufferLayout Vertex_P3_N3_T2_TAN3_BTAN_3::bufferLayout { {ShaderDataType::Float3, "pos"}, {ShaderDataType::Float3, "norm"}, {ShaderDataType::Float2, "tex_coord"},
                                                             {ShaderDataType::Float3, "tangent"}, {ShaderDataType::Float3, "bitangent"} };
}