#include "DeviceContext.h"
#include "MSwapChain.h"
#include "MVertexBuffer.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* context) : _deviceContex(context)
{
}

bool DeviceContext::ClearRenderTargetColor(MSwapChain* swap_chain, float r, float g, float b, float a)
{
    FLOAT clear_color[] = {r,g,b,a};
    _deviceContex->ClearRenderTargetView(swap_chain->_Rtv.Get(), clear_color);
    _deviceContex->OMSetRenderTargets(1, swap_chain->_Rtv.GetAddressOf(), NULL);

    return true;
}

bool DeviceContext::SetVertexBuffer(MVertexBuffer* vertex_buffer)
{ 
    UINT stride = vertex_buffer->_size_vertex;
    UINT offset = 0;
    _deviceContex->IASetVertexBuffers(0, 1, vertex_buffer->_buffer.GetAddressOf(), &stride, &offset);
    _deviceContex->IASetInputLayout(vertex_buffer->_layout.Get());

    return true;
}

void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_Index)
{
    _deviceContex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _deviceContex->Draw(vertex_count, start_vertex_Index);
}

void DeviceContext::DrawTriangleStrip(UINT vertex_count, UINT start_vertex_Index)
{
    _deviceContex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    _deviceContex->Draw(vertex_count, start_vertex_Index);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
    D3D11_VIEWPORT vp = {};
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    _deviceContex->RSSetViewports(1, &vp);
}

void DeviceContext::SetVertexShader(MVertexShader* vertex_shader)
{
    _deviceContex->VSSetShader(vertex_shader->_vsShader.Get(), nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixel_shader)
{
    _deviceContex->PSSetShader(pixel_shader->_psShader.Get(), nullptr, 0);
}

void DeviceContext::SetConstantBuffer(MVertexShader* vertex_shader, ConstantBuffer* buffer)
{
    _deviceContex->VSSetConstantBuffers(0, 1, buffer->_constBuffer.GetAddressOf());
}

void DeviceContext::SetConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer)
{
    _deviceContex->PSSetConstantBuffers(0, 1, buffer->_constBuffer.GetAddressOf());
}

bool DeviceContext::Realese()
{
    return true;
}

ComPtr<ID3D11DeviceContext> DeviceContext::GetDeviceContext()
{
    return _deviceContex;
}
