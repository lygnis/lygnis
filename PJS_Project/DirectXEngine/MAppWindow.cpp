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
	_view_cam = _camera->mat_view_;
	_proj_cam = _camera->mat_proj_;
}
void MAppWindow::UpdateLight()
{
	//_light_tor_y += 1.807f * Timer::get()->m_fDeltaTime;
	_light_position = TVector4(180,140,70,1.0f);
}

void MAppWindow::UpdateSkyBox()
{
	// 스카이 박스 업데이트
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(1000.f, 1000.f, 1000.f));
	TVector3 camWorld = _camera->camera_pos_;
	cc._world.Translation(camWorld);
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_skyMat->SetData(&cc, sizeof(Constant));
}

void MAppWindow::UpdateModel(TVector3 position, const std::vector<MaterialPtr>& list_material)
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
	temp.x = _camera->camera_pos_.x; temp.y = _camera->camera_pos_.y; temp.z = _camera->camera_pos_.z; temp.w = 1.0f;

	cc._cameraPos = temp;
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	cc._light_position = _light_position;
	cc._light_radius = _light_radius;

	cc._cTime = _time;
	for (size_t m = 0; m < list_material.size(); m++)
	{
		list_material[m]->SetData(&cc, sizeof(Constant));
	}
}

void MAppWindow::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
{
	// 오브젝트 렌더링
	// 버텍스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(mesh->getVertexBuffer());
	// 인덱스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(mesh->getIndexBuffer());

	// 현재 고려하고 있는 머티리얼을 여기서 그래픽 파이프라인에 바인딩한다.
	for (size_t m = 0; m < mesh->GetNumMaterialSlots(); m++)
	{
		if (m >= list_material.size())
			break;
		MaterialSlot mat = mesh->GetMaterialSlot(m);
		// 머티리얼 설정 방법을 사용하여 머티리얼을 그래픽 파이프 라인에 바인딩 한다.
		MGraphicsEngine::get()->SetMaterial(list_material[m]);
		
		MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(mat.num_indices, 0, mat.start_index);

	}
}

void MAppWindow::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	Input::get()->Init();
	InputSystem::get()->addListener(this);

	// 카메라 생성 및 초기화
	_camera = std::make_shared<DebugCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));

	// 텍스쳐 로딩
	//_wall_tex =	MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/wall.jpg");
	//_bricks_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick.png");
	//_earth_color_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/earth_color.jpg");
	_sky_Tex =			MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sky.jpg");
	_sand_tex =		MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sand.jpg");
	_barrel_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/barrel.jpg");
	_bricks_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/house_brick.jpg");
	_window_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/house_windows.jpg");
	_wood_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/house_wood.jpg");

	// 오브젝트 로딩
	//_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/scene.obj");
	//_mesh_torus = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/torus.obj");
	//_mesh_suzanne = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/suzanne.obj");
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");
	_terrain_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/terrain.obj");
	_house_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/house.obj");

	// 스왑체인 생성
	RECT rc = GetClientRect();
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right-rc.left,rc.bottom-rc.top);

	// 머티리얼 생성
	_mater = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"PointLightShader.hlsl");
	_mater->AddTexture(_wall_tex);
	_mater->SetCullMode(CULL_MODE_BACK);

	_terrain_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_terrain_mat->AddTexture(_sand_tex);
	_terrain_mat->SetCullMode(CULL_MODE_BACK);

	_barrel_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_barrel_mat->AddTexture(_barrel_tex);
	_barrel_mat->SetCullMode(CULL_MODE_BACK);

	_bricks_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_bricks_mat->AddTexture(_bricks_tex);
	_bricks_mat->SetCullMode(CULL_MODE_BACK);

	_window_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_window_mat->AddTexture(_window_tex);
	_window_mat->SetCullMode(CULL_MODE_BACK);

	_wood_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	_wood_mat->AddTexture(_wood_tex);
	_wood_mat->SetCullMode(CULL_MODE_BACK);

	//_bricks_mat = MGraphicsEngine::get()->CreateMaterial(_mater);
	//_bricks_mat->AddTexture(_bricks_tex);
	//_bricks_mat->SetCullMode(CULL_MODE_BACK);

	// 스카이 박스
	_skyMat = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"SkyBoxShader.hlsl");
	_skyMat->AddTexture(_sky_Tex);	
	_skyMat->SetCullMode(CULL_MODE_FRONT);

	_list_materials.reserve(32);
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

	// 카메라 라이트 스카이 박스 업데이트
	UpdateQuadPosition();

	// 렌더 .모델링
	// 밖에서 렌더링
	//UpdateModel(TVector3(0,0,0), _mater);
	//DrawMesh(_sky_mesh, _mater);
	//// 스카이 박스 그리기
	//// 안쪽에서도 렌더링

	//UpdateModel(TVector3(4, 0, 0), _earth_mat);
	//DrawMesh(_sky_mesh, _earth_mat);

	//UpdateModel(TVector3(-4, 0, 0), _bricks_mat);
	//DrawMesh(_sky_mesh, _bricks_mat);

	//UpdateModel(TVector3(-6, 0, 0), _bricks_mat);
	//DrawMesh(_mesh_torus, _bricks_mat);

	//UpdateModel(TVector3(6, 0, 0), _bricks_mat);
	//DrawMesh(_mesh_suzanne, _bricks_mat);

	_list_materials.clear();
	_list_materials.push_back(_barrel_mat);
	_list_materials.push_back(_bricks_mat);
	_list_materials.push_back(_window_mat);
	_list_materials.push_back(_wood_mat);
	_list_materials.push_back(_terrain_mat);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			UpdateModel(TVector3(-14.0f +14.0f *i, 0, -14.0f + 14.0f * j), _list_materials);
			DrawMesh(_house_mesh, _list_materials);
		}
	}
	_list_materials.clear();
	_list_materials.push_back(_terrain_mat);
	UpdateModel(TVector3(0, 0, 0), _list_materials);
	DrawMesh(_terrain_mesh, _list_materials);

	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);

	// 버퍼 바꾸기
	_swapChain->Present(true);
	// 상수버퍼 시간 갱신
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
	_swapChain->Resize(rc.right, rc.bottom);
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(rc.right) / (float)(rc.bottom));
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