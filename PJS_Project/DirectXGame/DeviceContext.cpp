#include "DeviceContext.h"
#include "MSwapChain.h"
#include "MVertexBuffer.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include <exception>

DeviceContext::DeviceContext(ID3D11DeviceContext* context, RenderSystem* system) : _deviceContex(context), _system(system)
{
}

bool DeviceContext::ClearRenderTargetColor(const SwapChainPtr &swap_chain, float r, float g, float b, float a)
{
    FLOAT clear_color[] = {r,g,b,a};
    _deviceContex->ClearRenderTargetView(swap_chain->_Rtv.Get(), clear_color);
    _deviceContex->ClearDepthStencilView(swap_chain->_Dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    _deviceContex->OMSetRenderTargets(1, swap_chain->_Rtv.GetAddressOf(), swap_chain->_Dsv.Get());

    return true;
}

bool DeviceContext::SetVertexBuffer(const MVertexBufferPtr &vertex_buffer)
{ 
    UINT stride = vertex_buffer->_size_vertex;
    UINT offset = 0;
    _deviceContex->IASetVertexBuffers(0, 1, vertex_buffer->_buffer.GetAddressOf(), &stride, &offset);
    _deviceContex->IASetInputLayout(vertex_buffer->_layout.Get());

    return true;
}

bool DeviceContext::SetIndexBuffer(const IndexBufferPtr& index_buffer)
{
    _deviceContex->IASetIndexBuffer(index_buffer->_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    return false;
}

void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_Index)
{
    _deviceContex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _deviceContex->Draw(vertex_count, start_vertex_Index);
}

void DeviceContext::DrawIndexTriangleList(UINT index_count, UINT start_vertex_Index, UINT start_index_location)
{
    _deviceContex->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _deviceContex->DrawIndexed(index_count, start_index_location, start_vertex_Index);
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

void DeviceContext::SetVertexShader(const MVertexShaderPtr& vertex_shader)
{
    _deviceContex->VSSetShader(vertex_shader->_vsShader.Get(), nullptr, 0);
}

void DeviceContext::SetPixelShader(const PixelShaderPtr& pixel_shader)
{
    _deviceContex->PSSetShader(pixel_shader->_psShader.Get(), nullptr, 0);
}

void DeviceContext::SetConstantBuffer(const MVertexShaderPtr &vertex_shader, const ConstantBufferPtr& buffer)
{
    _deviceContex->VSSetConstantBuffers(0, 1, buffer->_constBuffer.GetAddressOf());
}

void DeviceContext::SetConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer)
{
    _deviceContex->PSSetConstantBuffers(0, 1, buffer->_constBuffer.GetAddressOf());
}

void DeviceContext::SetTexture(const MVertexShaderPtr& vertex_shader, const TexturePtr &texture)
{
    _deviceContex->VSSetShaderResources(0, 1, &texture->_srview);
}

void DeviceContext::SetTexture(const PixelShaderPtr& pixel_shader, const TexturePtr &texture)
{
    _deviceContex->PSSetShaderResources(0, 1, &texture->_srview);
}


ComPtr<ID3D11DeviceContext> DeviceContext::GetDeviceContext()
{
    return _deviceContex;
}
