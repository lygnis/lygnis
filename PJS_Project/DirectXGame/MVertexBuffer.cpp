#include "MVertexBuffer.h"
//#include "MGraphicsEngine.h"

bool MVertexBuffer::Load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
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
    
    hr = MGraphicsEngine::get()->_d3d_Device->CreateBuffer(&buffDesc, &init_data, &_buffer);
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        // ½¦ÀÌ´õ ³Ñ±æ Á¤º¸
        // ½Ã¸àÆ½ ÀÌ¸§, ½Ã¸àÆ½ ÀÎµ¦½º, Æ÷¸Ë, ÀÔ·Â ½½·Ô, ¹ÙÀÌÆ® ¿ÀÇÁ¼Â, ÀÔ·Â ½½·Ô Å¬·¡½º, 
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}

    };
    UINT size_layout = ARRAYSIZE(layout);

    hr = MGraphicsEngine::get()->_d3d_Device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader,_layout.GetAddressOf());
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    return true;
}

UINT MVertexBuffer::GetSizeVertexList()
{
    return _size_list;
}

bool MVertexBuffer::Release()
{
    return true;
}
