#include "MAppWindow.h"
#include "MVertexBuffer.h"
#include <Windows.h>
#include "InputSystem.h"
#include "Mesh.h"
struct vertex
{
	TVector3 position;
	//TVector3 position1;
	TVector2 texcoord;
};

__declspec(align(16))
struct Constant
{
	TMatrix _world;
	TMatrix _view;
	TMatrix _proj;
	UINT _time;

};

void MAppWindow::UpdateQuadPosition()
{
	Constant cc;
	cc._time = ::GetTickCount();
	cc._world.Identity;

	TMatrix temp;
	temp.Identity;
	temp = TMatrix::CreateRotationX(_rot_x);
	TMatrix cam;
	cam = cam.Identity;
	cam =cam* temp;
	temp = temp.Identity;
	temp = TMatrix::CreateRotationY(_rot_y);
	cam = cam* temp;
	cam.Translation(TVector3(0, _camPos, -3));
	cam = cam.Invert();

	cc._view = cam;
	//cc._proj = TMatrix::CreateOrthographic((this->GetClientRect().right - this->GetClientRect().left)/400.0f, 
		//					 (this->GetClientRect().bottom - this->GetClientRect().top)/400.0f, -4.0f, 4.0f);
	int width = (this->GetClientRect().right - this->GetClientRect().left);
	int height = (this->GetClientRect().bottom - this->GetClientRect().top);

	cc._proj = TMatrix::CreatePerspectiveFieldOfView(3.141592*0.5f , (this->GetClientRect().right) / (this->GetClientRect().bottom), 1.0f, 100.f);
	_cb->Update(MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void MAppWindow::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	//MWindow::OnCreate();
	InputSystem::get()->addListener(this);


	_wood_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick.png");
	_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/teapot.obj");

	RECT rc = GetClientRect();

	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right-rc.left,rc.bottom-rc.top);

	TVector3 position_list[] =
	{
		// 앞면
		{TVector3(-0.5f, -0.5f, -0.5f)},
		{TVector3(-0.5f, 0.5f, -0.5f)},
		{TVector3(0.5f, 0.5f, -0.5f)},
		{TVector3(0.5f, -0.5f, -0.5f)},

		// 뒷면
		{TVector3(0.5f, -0.5f, 0.5f)},
		{TVector3(0.5f, 0.5f, 0.5f)},
		{TVector3(-0.5f, 0.5f, 0.5f)},
		{TVector3(-0.5f, -0.5f, 0.5f)}
	};

	TVector2 texcoord_list[] =
	{
		// 앞면
		{TVector2(0.0f, 0.0f)},
		{TVector2(0.0f, 1.0f)},
		{TVector2(1.0f, 0.0f  )},
		{TVector2(1.0f, 1.0f)}		   
	};

	vertex vertex_list[] =
	{
		{position_list[0], texcoord_list[1]},
		{position_list[1], texcoord_list[0]},
		{position_list[2], texcoord_list[2]},
		{position_list[3], texcoord_list[3]},

		{position_list[4], texcoord_list[1]},
		{position_list[5], texcoord_list[0]},
		{position_list[6], texcoord_list[2]},
		{position_list[7], texcoord_list[3]},

		{position_list[1], texcoord_list[1]},
		{position_list[6], texcoord_list[0]},
		{position_list[5], texcoord_list[2]},
		{position_list[2], texcoord_list[3]},

		{position_list[7], texcoord_list[1]},
		{position_list[0], texcoord_list[0]},
		{position_list[3], texcoord_list[2]},
		{position_list[4], texcoord_list[3]},

		{position_list[3], texcoord_list[1]},
		{position_list[2], texcoord_list[0]},
		{position_list[5], texcoord_list[2]},
		{position_list[4], texcoord_list[3]},

		{position_list[7], texcoord_list[1]},
		{position_list[6], texcoord_list[0]},
		{position_list[1], texcoord_list[2]},
		{position_list[0], texcoord_list[3]}
	};

	UINT size_list = ARRAYSIZE(vertex_list);

	UINT index_list[] =
	{
		// 앞 
		 0,1,2,    //1번 삼각형 
		 2,3,0,     //2번 삼각형
		// 뒷 
		 4,5,6,
		 6,7,4,
		// 윗 
		 8,9,10,
		 10,11,8,
		// 아래 
		 12,13,14,
		 14,15,12,
		// 오른쪽 
		 16,17,18,
		 18,19,16,
		// 왼쪽 
		 20,21,22,
		 22,23,20
	};
	UINT size_index_list = ARRAYSIZE(index_list);
	_ib = MGraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer(index_list, size_index_list);

	// 쉐이더 컴파일
	void* shader_byte_code = nullptr;
	size_t size_shader =0;
	MGraphicsEngine::get()->getRenderSystem()->CompileVertexShader(L"VertexShader.hlsl", "mainvs", &shader_byte_code, &size_shader);
	_vs = std::move(MGraphicsEngine::get()->getRenderSystem()->CreateVertexShader(shader_byte_code, size_shader));

	_vb = MGraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(L"PixelShader.hlsl", "mainps", &shader_byte_code, &size_shader);
	_ps = std::move(MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader));


	Constant cc;
	cc._time = 0;
	// 상수버퍼 클래스 할당
	_cb = MGraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(&cc, sizeof(Constant));
}

void MAppWindow::OnUpdate()
{
	Timer::get()->Frame();
	//MAppWindow::OnUpdate();
	// 
	InputSystem::get()->Update();
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		1,1,1,1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	// 상수버퍼 수정 후 업데이트
	UpdateQuadPosition();
	



	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(_vs, _cb);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(_ps, _cb);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(_vs);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(_ps);

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(_ps, _wood_tex);
	// 오브젝트 렌더링
	// 버텍스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(_mesh->getVertexBuffer());
	// 인덱스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(_mesh->getIndexBuffer());

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(_mesh->getIndexBuffer()->GetSizeIndexList(),0, 0);
	// 버퍼 바꾸기
	_swapChain->Present(false);

	// 시간 구하기
	_oldDelta = _newDelta;
	_newDelta = ::GetTickCount();
	_deltaTime = (_oldDelta)? ((_newDelta - _oldDelta) /1000.0f) : 0;
}

void MAppWindow::OnDestroy()
{
	_wood_tex.reset();

	MWindow::OnDestroy();
}

void MAppWindow::OnFocus()
{
	InputSystem::get()->addListener(this);
}

void MAppWindow::OnKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void MAppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		_camPos += 1.14f * _deltaTime;
	}
	else if (key == 'S')
	{
		_camPos -= 1.14f * _deltaTime;
	}
	else if (key == 'A')
	{
		_rot_y += 1.14f * _deltaTime;
	}
	else if (key == 'D')
	{
		_rot_y -= 1.14f * _deltaTime;
	}
	else if (key == 'Q')
	{
		_rot_x += 1.14f * _deltaTime;
	}
}

void MAppWindow::onKeyUp(int key)
{
	
}

void MAppWindow::OnMouseMove(const Point& delta_mouse_pos)
{
	_rot_x += delta_mouse_pos._y * 5 * Timer::get()->m_fDeltaTime;
	_rot_y += delta_mouse_pos._x * 5 * Timer::get()->m_fDeltaTime;
}


void MAppWindow::OnLeftMouseDown(const Point& delta_mouse_pos)
{
}

void MAppWindow::OnLeftMouseUp(const Point& delta_mouse_pos)
{
}

void MAppWindow::OnRightMouseDown(const Point& delta_mouse_pos)
{
}

void MAppWindow::OnRightMouseUp(const Point& delta_mouse_pos)
{
}
