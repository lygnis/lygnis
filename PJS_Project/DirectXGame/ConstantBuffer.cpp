#include "ConstantBuffer.h"
#include "RenderSystem.h"
#include "DeviceContext.h"
#include <exception>

ConstantBuffer::ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system) : _system(system)
{
    HRESULT hr;

    D3D11_BUFFER_DESC buffDesc = {};
    buffDesc.Usage = D3D11_USAGE_DEFAULT;
    buffDesc.ByteWidth = size_buffer;
    buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    buffDesc.CPUAccessFlags = 0;
    buffDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = buffer;

    hr = _system->_d3d_Device->CreateBuffer(&buffDesc, &init_data, &_constBuffer);
    if (FAILED(hr))
    {
        assert(false);
        throw std::exception("ConstBuffer not create successfully");
    }
}


void ConstantBuffer::Update(DeviceContextPtr context, void* buffer)
{
    // 상수버퍼 업데이트
    context->_deviceContex->UpdateSubresource(_constBuffer.Get(), NULL, NULL, buffer, NULL,NULL);
}
