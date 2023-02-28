#include "MVertexBuffer.h"
#include "RenderSystem.h"
#include <exception>

MVertexBuffer::MVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader ,RenderSystem* system) : _system(system), _layout(0), _buffer(0)
{ 
    HRESULT hr;




    D3D11_BUFFER_DESC buffDesc = {};
    buffDesc.Usage = D3D11_USAGE_DEFAULT;
    buffDesc.ByteWidth = size_vertex * size_list;
    buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffDesc.CPUAccessFlags = 0;
    buffDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_vertices;
    _size_vertex = size_vertex;
    _size_list = size_list;
    
    hr = _system->_d3d_Device->CreateBuffer(&buffDesc, &init_data, &_buffer);
    if (FAILED(hr))
    {
        assert(false);
        throw std::exception("VertexBuffer not create successfully");
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        // ½¦ÀÌ´õ ³Ñ±æ Á¤º¸
        // ½Ã¸àÆ½ ÀÌ¸§, ½Ã¸àÆ½ ÀÎµ¦½º, Æ÷¸Ë, ÀÔ·Â ½½·Ô, ¹ÙÀÌÆ® ¿ÀÇÁ¼Â, ÀÔ·Â ½½·Ô Å¬·¡½º, 
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT size_layout = ARRAYSIZE(layout);

    hr = _system->_d3d_Device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader,_layout.GetAddressOf());
    if (FAILED(hr))
    {
        assert(false);
        throw std::exception("Layout not create successfully");
    }
}

UINT MVertexBuffer::GetSizeVertexList()
{
    return _size_list;
}

