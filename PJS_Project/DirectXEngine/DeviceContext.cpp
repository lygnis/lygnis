#include "DeviceContext.h"
#include "MSwapChain.h"
#include "MVertexBuffer.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include <exception>
#include "Texture2D.h"
DeviceContext::DeviceContext(ID3D11DeviceContext* context, RenderSystem* system) : _deviceContex(context), _system(system)
{
}

bool DeviceContext::ClearRenderTargetColor(const SwapChainPtr &swap_chain, float r, float g, float b, float a)
{
    FLOAT clear_color[] = {r,g,b,a};
    auto rtv = swap_chain->_Rtv.Get();
    auto dsv = swap_chain->_Dsv.Get();

    _deviceContex->ClearRenderTargetView(rtv, clear_color);
    _deviceContex->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    _deviceContex->OMSetRenderTargets(1, &rtv, swap_chain->_Dsv.Get());

    return true;
}

void DeviceContext::ClearDepthStencil(const SwapChainPtr& swap_chain)
{
    auto dsv = swap_chain->_Dsv.Get();
    _deviceContex->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

//bool DeviceContext::ClearRenderTargetColor(const TexturePtr& render_target, float r, float g, float b, float a)
//{
//    if (render_target->t_type_ != Texture::Type::RENDERTARGET)
//        return false;
//    FLOAT clear_color[] = { r,g,b,a };
//    _deviceContex->ClearRenderTargetView(render_target->render_target_view_.Get(), clear_color);
//}

//void DeviceContext::ClearDepthStencil(const TexturePtr& depth_stencil)
//{
//    if (depth_stencil->t_type_ != Texture::Type::DEPTHSTECIL)
//        return;
//    _deviceContex->ClearDepthStencilView(depth_stencil->depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
//}
//
//void DeviceContext::SetRenderTarget(const TexturePtr& render_target, const TexturePtr& depth_stencil)
//{
//    if (render_target->t_type_ != Texture::Type::RENDERTARGET)
//        return;
//    if (depth_stencil->t_type_ != Texture::Type::DEPTHSTECIL)
//        return;
//    _deviceContex->OMSetRenderTargets(1, render_target->render_target_view_.GetAddressOf(), depth_stencil->depth_stencil_view_.Get());
//}

bool DeviceContext::SetVertexBuffer(const MVertexBufferPtr &vertex_buffer)
{ 
    UINT stride = vertex_buffer->_size_vertex;
    UINT offset = 0;
    auto buffer = vertex_buffer->_buffer.Get();
    _deviceContex->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
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

void DeviceContext::SetConstantBuffer(const ConstantBufferPtr& buffer)
{
    auto buf = buffer->_constBuffer.Get();
    _deviceContex->VSSetConstantBuffers(0, 1, &buf);
    _deviceContex->PSSetConstantBuffers(0, 1, &buf);
}

//void DeviceContext::SetTexture(const MVertexShaderPtr& vertex_shader, const TexturePtr* texture, UINT num_textures)
//{
//    // ���̴����� �˻� �� �� �ְ�
//    ComPtr<ID3D11ShaderResourceView> list_res[32];
//    ID3D11SamplerState* list_sampler[32];
//    for (UINT i = 0; i < num_textures; i++)
//    {
//        list_res[i] = texture[i]->_srview;
//        list_sampler[i] = texture[i]->_sampler_state;
//    }
//    // �ؽ�ó ����� ���̴��� �����ϱ� ���� ��� ���� �ؽ��� ���� ��Ÿ���� ���� �߰�
//    _deviceContex->VSSetShaderResources(0, 1, list_res->GetAddressOf());
//    _deviceContex->VSSetSamplers(0, num_textures, list_sampler);
//}
//
void DeviceContext::SetTexture(const Texture2DPtr* texture, UINT num_textures)
{
    // ���̴����� �˻� �� �� �ְ�
   ID3D11ShaderResourceView* list_res[32];
   ID3D11SamplerState* list_sampler[32];
    for (UINT i = 0; i < num_textures; i++)
    {
        list_res[i] = texture[i]->_srview.Get();
        list_sampler[i] = texture[i]->_sampler_state.Get();
    }
    // �ؽ�ó ����� ���̴��� �����ϱ� ���� ��� ���� �ؽ��� ���� ��Ÿ���� ���� �߰�
    _deviceContex->VSSetShaderResources(0, 1, list_res);
    _deviceContex->VSSetSamplers(0, num_textures, list_sampler);
    _deviceContex->PSSetShaderResources(0, num_textures, list_res);
    _deviceContex->PSSetSamplers(0, num_textures, list_sampler);
}


ID3D11DeviceContext* DeviceContext::GetDeviceContext()
{
    return _deviceContex.Get();
}