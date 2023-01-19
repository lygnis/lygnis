#include "MAppWindow.h"
#include "MVertexBuffer.h"
struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

void MAppWindow::OnCreate()
{
	//MWindow::OnCreate();
	MGraphicsEngine::get()->Init();
	_swapChain = MGraphicsEngine::get()->CreateSwapChain();

	RECT rc = this->GetClientRect();
	_swapChain->Init(this->_hwnd, rc.right-rc.left,rc.bottom-rc.top);
	vertex sc;
	vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
	};
	_vb = MGraphicsEngine::get()->CreateVertexBuffer();

	UINT size_list = ARRAYSIZE(list);
	MGraphicsEngine::get()->CreateShader();
	void* shader_byte_code = nullptr;
	UINT size_shader =0;
	MGraphicsEngine::get()->GetShaderBufferSize(&shader_byte_code, &size_shader);

	_vb->Load(list,sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void MAppWindow::OnUpdate()
{
	//MAppWindow::OnUpdate();
	MGraphicsEngine::get()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain.get(),
		1,0,0,1);
	RECT rc = this->GetClientRect();

	MGraphicsEngine::get()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	MGraphicsEngine::get()->SetShader();
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetVertexBuffer(_vb.get());
	MGraphicsEngine::get()->getImmediateDeviceContext()->DrawTriangleStrip(_vb->GetSizeVertexList(), 0);

	_swapChain->Present(false);
}

void MAppWindow::OnDestroy()
{
	MWindow::OnDestroy();
}
