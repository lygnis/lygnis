#pragma once
#include "MStd.h"


class DeviceContext
{
public:
	DeviceContext() {}
	DeviceContext(ID3D11DeviceContext* context, RenderSystem* system);
	~DeviceContext() {}

public:
	bool ClearRenderTargetColor(const SwapChainPtr& swap_chain , float r, float g, float b, float a);
	void ClearDepthStencil(const SwapChainPtr& swap_chain);

	//bool ClearRenderTargetColor(const TexturePtr& render_target, float r, float g, float b, float a);
	//void ClearDepthStencil(const TexturePtr& depth_stencil);

	//void SetRenderTarget(const TexturePtr& render_target, const TexturePtr& depth_stencil);

	bool SetVertexBuffer(const MVertexBufferPtr &vertex_buffer);
	bool SetIndexBuffer(const IndexBufferPtr &index_buffer);

	void DrawTriangleList(UINT vertex_count, UINT start_vertex_Index);
	void DrawIndexTriangleList(UINT index_count ,UINT start_vertex_Index , UINT start_index_location);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_Index);
	void SetViewportSize(UINT width, UINT height);

	void SetVertexShader(const MVertexShaderPtr& vertex_shader);
	void SetPixelShader(const PixelShaderPtr& pixel_shader);

	void SetConstantBuffer(const MVertexShaderPtr &vertex_shader, const ConstantBufferPtr &buffer);
	void SetConstantBuffer(const PixelShaderPtr &pixel_shader, const ConstantBufferPtr &buffer);

	//void SetTexture(const MVertexShaderPtr& vertex_shader, const TexturePtr* texture, UINT num_textures);
	//void SetTexture(const PixelShaderPtr& pixel_shader, const TexturePtr* texture, UINT num_textures);

	ID3D11DeviceContext* GetDeviceContext();
private:
	ComPtr<ID3D11DeviceContext> _deviceContex;
	RenderSystem* _system = nullptr;
private:
	friend class ConstantBuffer;
};

