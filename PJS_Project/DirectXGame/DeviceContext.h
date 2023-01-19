#pragma once
#include "MStd.h"

class MSwapChain;
class MVertexBuffer;

class DeviceContext
{
public:
	DeviceContext() {}
	DeviceContext(ID3D11DeviceContext* context);
	~DeviceContext() {}

public:
	bool ClearRenderTargetColor(MSwapChain* swap_chain , float r, float g, float b, float a);
	bool SetVertexBuffer(MVertexBuffer* vertex_buffer);
	void DrawTriangleList(UINT vertex_count, UINT start_vertex_Index);
	void DrawTriangleStrip(UINT vertex_count, UINT start_vertex_Index);
	void SetViewportSize(UINT width, UINT height);
	bool Realese();
	ComPtr<ID3D11DeviceContext> GetDeviceContext();
private:
	ComPtr<ID3D11DeviceContext> _deviceContex;

};

