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
	TVector4 _light_dir;
	TVector4 _cameraPos;
	TVector4 _light_position = TVector4(0,1,0,0);
	float _light_radius;
	float _cTime = 0.0f;
};



void MAppWindow::UpdateQuadPosition()
{
	UpdateCamera();
	UpdateLight();
	UpdateSkyBox();
}

void MAppWindow::UpdateCamera()
{
	_camera->Frame();
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	_view_cam = _camera->m_matView;
	_proj_cam = _camera->m_matProj;
}
void MAppWindow::UpdateLight()
{
	_light_tor_y += 1.807f * Timer::get()->m_fDeltaTime;
	float dist_from_origin = 3.0f;
	_light_position = TVector4(cos(_light_tor_y) * dist_from_origin, 3.1f, sin(_light_tor_y) * dist_from_origin, 3.1f);
}

void MAppWindow::UpdateModel(TVector3 position, const MaterialPtr& material)
{
	Constant cc;
	cc._world.Identity;
	cc._world.Translation(position);
	TMatrix _light_rot_mat;
	_light_rot_mat.Identity;
	_light_rot_mat = TMatrix::CreateRotationY(_light_tor_y);

	TVector3 temp_light = _light_rot_mat.Backward();
	cc._light_dir.x = temp_light.x; cc._light_dir.y = temp_light.y; cc._light_dir.z = temp_light.z; cc._light_dir.w = 1.0f;
	TVector4 temp;
	temp.x = _camera->m_vCameraPos.x; temp.y = _camera->m_vCameraPos.y; temp.z = _camera->m_vCameraPos.z; temp.w = 1.0f;

	cc._cameraPos = temp;
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	cc._light_position = _light_position;
	cc._light_radius = _light_radius;

	cc._cTime = _time;
	material->SetData(&cc, sizeof(Constant));
}

void MAppWindow::UpdateSkyBox()
{
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(100.f, 100.f, 100.f));
	TVector3 camWorld = _camera->m_vCameraPos;
	cc._world.Translation(camWorld);
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_skyMat->SetData(&cc, sizeof(Constant));
}



void MAppWindow::DrawMesh(const MeshPtr& mesh, const MaterialPtr& material)
{
	// 머티리얼 설정 방법을 사용하여 머티리얼을 그래픽 파이프 라인에 바인딩 한다.
	MGraphicsEngine::get()->SetMaterial(material);
	// 오브젝트 렌더링
	// 버텍스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(mesh->getVertexBuffer());
	// 인덱스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(mesh->getIndexBuffer());

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(mesh->getIndexBuffer()->GetSizeIndexList(), 0, 0);
}

void MAppWindow::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	Input::get()->Init();
	//MWindow::OnCreate();
	InputSystem::get()->addListener(this);

	_camera = std::make_shared<DebugCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));

	_wall_tex =	MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/wall.jpg");
	_bricks_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick.png");
	_earth_color_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/earth_color.jpg");

	_sky_Tex =			MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/stars_map.jpg");
	// 밤 낮 구분
	//_earth_night_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/earth_night.jpg");

	_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/scene.obj");
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");

	RECT rc = GetClientRect();

	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right-rc.left,rc.bottom-rc.top);

	_mater = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"PointLightShader.hlsl");
	_mater->AddTexture(_wall_tex);
	_mater->SetCullMode(CULL_MODE_BACK);

	_earth_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_earth_mat->AddTexture(_earth_color_tex);
	_earth_mat->SetCullMode(CULL_MODE_BACK);

	_bricks_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_bricks_mat->AddTexture(_bricks_tex);
	_bricks_mat->SetCullMode(CULL_MODE_BACK);

	// 스카이 박스
	_skyMat = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"SkyBoxShader.hlsl");
	_skyMat->AddTexture(_sky_Tex);	
	_skyMat->SetCullMode(CULL_MODE_FRONT);
}

void MAppWindow::OnUpdate()
{
	Timer::get()->Frame();
	Input::get()->Frame();
	if (Input::get()->GetKey('F') == KEY_UP)
	{
		_fullscreen_state = !_fullscreen_state;
		RECT size_screen = this->GetSizeScreen();

		_swapChain->SetFullScreen(_fullscreen_state, size_screen.right, size_screen.bottom);
	}
	if (Input::get()->GetKey(VK_F10) == KEY_HOLD)
	{
		_light_radius -= 1.0f * Timer::get()->m_fDeltaTime;
	}
	if (Input::get()->GetKey(VK_F11) == KEY_HOLD)
	{
		_light_radius += 1.0f * Timer::get()->m_fDeltaTime;
	}
	this->Render();
}

void MAppWindow::Render()
{
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		0.2, 0.2, 0.2, 1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	// 상수버퍼 수정 후 업데이트
	UpdateQuadPosition();
	// 렌더 .모델링
	// 밖에서 렌더링

	UpdateModel(TVector3(0,0,0), _mater);
	DrawMesh(_sky_mesh, _mater);
	// 스카이 박스 그리기
	// 안쪽에서도 렌더링

	UpdateModel(TVector3(4, 0, 0), _earth_mat);
	DrawMesh(_sky_mesh, _earth_mat);

	UpdateModel(TVector3(-4, 0, 0), _bricks_mat);
	DrawMesh(_sky_mesh, _bricks_mat);

	//UpdateModel(TVector3(0, 0, 0), _skyMat);
	DrawMesh(_sky_mesh, _skyMat);
	// 버퍼 바꾸기
	_swapChain->Present(true);
	_time += Timer::get()->m_fDeltaTime;
}

void MAppWindow::OnDestroy()
{
	MWindow::OnDestroy();
	_swapChain->SetFullScreen(false, 1, 1);
}

void MAppWindow::OnFocus()
{
	InputSystem::get()->addListener(this);
}

void MAppWindow::OnKillFocus()
{
	InputSystem::get()->removeListener(this);
}
void MAppWindow::OnSize()
{
	RECT rc = this->GetClientRect();
	//MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->GetDeviceContext()->OMSetRenderTargets(0, nullptr, NULL);
	_swapChain->Resize(rc.right, rc.bottom);
	Render();
}

void MAppWindow::onKeyDown(int key)
{
	
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



TMatrix MAppWindow::RotationY(float fRad)
{
	float _fCostheta = cos(fRad);
	float _fSintheta = sin(fRad);
	TMatrix _mat;
	_mat._11 = cos(fRad); _mat._13 = -sin(fRad);
	_mat._31 = sin(fRad); _mat._33 = cos(fRad);
	return _mat;

	//float _fCostheta = cos(fRad);
	//float _fSintheta = sin(fRad);
	//TMatrix _mat;
	//_mat._22 = _fCostheta; _mat._23 = _fSintheta;
	//_mat._32 = -_fSintheta; _mat._33 = _fCostheta;
	//return _mat;
	/*float _fCostheta = cos(fRad);
	float _fSintheta = sin(fRad);
	TMatrix _mat;
	_mat._11 = _fCostheta; _mat._12 = -_fSintheta;
	_mat._21 = _fSintheta; _mat._22 = _fCostheta;
	return _mat;*/
}
