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

void DeviceContext::SetTexture(const MVertexShaderPtr& vertex_shader, const TexturePtr* texture, UINT num_textures)
{
    // 쉐이더에서 검색 할 수 있게
    ComPtr<ID3D11ShaderResourceView> list_res[32];
    ID3D11SamplerState* list_sampler[32];
    for (UINT i = 0; i < num_textures; i++)
    {
        list_res[i] = texture[i]->_srview;
        list_sampler[i] = texture[i]->_sampler_state;
    }
    // 텍스처 목록을 쉐이더에 전달하기 위해 목록 내에 텍스쳐 수를 나타내는 변수 추가
    _deviceContex->VSSetShaderResources(0, 1, list_res->GetAddressOf());
    _deviceContex->VSSetSamplers(0, num_textures, list_sampler);
}

void DeviceContext::SetTexture(const PixelShaderPtr& pixel_shader, const TexturePtr* texture, UINT num_textures)
{
    // 쉐이더에서 검색 할 수 있게
   ID3D11ShaderResourceView* list_res[32];
   ID3D11SamplerState* list_sampler[32];
    for (UINT i = 0; i < num_textures; i++)
    {
        list_res[i] = texture[i]->_srview;
        list_sampler[i] = texture[i]->_sampler_state;
    }
    // 텍스처 목록을 쉐이더에 전달하기 위해 목록 내에 텍스쳐 수를 나타내는 변수 추가
    _deviceContex->PSSetShaderResources(0, num_textures, list_res);
    _deviceContex->PSSetSamplers(0, num_textures, list_sampler);
}


ID3D11DeviceContext* DeviceContext::GetDeviceContext()
{
    return _deviceContex.Get();
}
