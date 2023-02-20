#include "IndexBuffer.h"
#include "RenderSystem.h"
#include <exception>

IndexBuffer::IndexBuffer(void* list_indices, UINT size_list ,RenderSystem* system) : _system(system), _buffer(0)
{
    HRESULT hr;

    D3D11_BUFFER_DESC buffDesc = {};
    buffDesc.Usage = D3D11_USAGE_DEFAULT;
    buffDesc.ByteWidth = 4 * size_list;
    buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffDesc.CPUAccessFlags = 0;
    buffDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = list_indices;
    _size_list = size_list;

    hr = _system->_d3d_Device->CreateBuffer(&buffDesc, &init_data, &_buffer);
    if (FAILED(hr))
    {
        assert(false);
        throw std::exception("IndexBuffer not create successfully");
    }
}

UINT IndexBuffer::GetSizeIndexList()
{
    return _size_list;
}
