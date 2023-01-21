#include "MAppWindow.h"
#include "MVertexBuffer.h"
#include <Windows.h>
struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
};

__declspec(align(16))
struct Constant
{
	UINT _time;

};

void MAppWindow::OnCreate()
{
	//MWindow::OnCreate();
	MGraphicsEngine::get()->Init();
	_swapChain = MGraphicsEngine::get()->CreateSwapChain();

	RECT rc = GetClientRect();
	_swapChain->Init(_hwnd, rc.right-rc.left,rc.bottom-rc.top);
	vertex sc;
	vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f, -0.32f,-0.11f, 0.0f	,1,0,0},
		{-0.5f, 0.5f, 0.0f, -0.11f, 0.78f, 0.0f		, 0,1,0},
		{0.5f, -0.5f, 0.0f	, 0.75f,-0.73f, 0.0f	, 0,0,1},
		{0.5f, 0.5f, 0.0f, 0.88f, 0.77f,0.0f		, 1,1,0},
	};

	UINT size_list = ARRAYSIZE(list);

	_vb = MGraphicsEngine::get()->CreateVertexBuffer();

	// 쉐이더 컴파일
	void* shader_byte_code = nullptr;
	size_t size_shader =0;
	MGraphicsEngine::get()->CompileVertexShader(L"VertexShader.hlsl", "mainvs", &shader_byte_code, &size_shader);
	_vs = std::move(MGraphicsEngine::get()->CreateVertexShader(shader_byte_code, size_shader));
	_vb->Load(list,sizeof(vertex), size_list, shader_byte_code, size_shader);

	MGraphicsEngine::get()->CompilePixelShader(L"PixelShader.hlsl", "mainps", &shader_byte_code, &size_shader);
	_ps = std::move(MGraphicsEngine::get()->CreatePixelShader(shader_byte_code, size_shader));


	Constant cc;
	cc._time = 0;
	// 상수버퍼 클래스 할당
	_cb = MGraphicsEngine::get()->CreateConstantBuffer();
	_cb->Load(&cc, sizeof(Constant));

}

void MAppWindow::OnUpdate()
{
	//MAppWindow::OnUpdate();
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain.get(),
		0,0,0,1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	Constant cc;
	cc._time = ::GetTickCount();
	_cb->Update(MGraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetConstantBuffer(_vs.get(), _cb.get());
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetConstantBuffer(_ps.get(), _cb.get());
	// 쉐이더 설정
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetVertexShader(_vs.get());
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetPixelShader(_ps.get());
	// 오브젝트 렌더링
	MGraphicsEngine::get()->getImmediateDeviceContext()->SetVertexBuffer(_vb.get());
	MGraphicsEngine::get()->getImmediateDeviceContext()->DrawTriangleStrip(_vb->GetSizeVertexList(), 0);
	// 버퍼 바꾸기
	_swapChain->Present(false);
}

void MAppWindow::OnDestroy()
{
	MWindow::OnDestroy();
}
