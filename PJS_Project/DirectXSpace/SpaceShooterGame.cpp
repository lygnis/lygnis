#include "SpaceShooterGame.h"
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
	TVector4 _light_position = TVector4(0, 1, 0, 0);
	float _light_radius;
	float _cTime = 0.0f;
};



void SpaceShooterGame::UpdateQuadPosition()
{
	UpdateThirdPersonCamera();
	UpdateLight();
	UpdateSkyBox();
	UpdateSpaceShip();
}

void SpaceShooterGame::UpdateCamera()
{
	_camera->Frame();
	_view_cam = _camera->m_matView;
	_proj_cam = _camera->m_matProj;
}
void SpaceShooterGame::UpdateThirdPersonCamera()
{
	_camera->target_pos_ = spaceship_pos_;
	_camera->Frame();
	_view_cam = _camera->m_matView;
	_proj_cam = _camera->m_matProj;
}
void SpaceShooterGame::UpdateLight()
{
	//_light_tor_y += 1.807f * Timer::get()->m_fDeltaTime;
	TMatrix temp;
	temp.Identity;
	_light_rot_matrix.Identity;
	temp.Identity;
	temp = TMatrix::CreateRotationX(-0.707f);
	_light_rot_matrix *= temp;
	temp.Identity;
	temp = TMatrix::CreateRotationY(0.807f);
	_light_rot_matrix *= temp;
}

void SpaceShooterGame::UpdateSpaceShip()
{
	space_world.Identity;
	TVector3 _vPos = _camera->m_vCameraPos + space_world.Backward() * (_camera->target_distance_) + space_world.Up()* -5.0f;
	::TQuaternion qRotation;
	::D3DXQuaternionRotationYawPitchRoll(&qRotation, _camera->m_fYaw, _camera->m_fPitch, _camera->m_fRoll);
	::D3DXMatrixAffineTransformation(&space_world, 1.0f, NULL, &qRotation, &_vPos);
}

void SpaceShooterGame::UpdateSkyBox()
{
	// 스카이 박스 업데이트
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(1000.f, 1000.f, 1000.f));
	TVector3 camWorld = _camera->m_vCameraPos;
	cc._world.Translation(camWorld);
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_skyMat->SetData(&cc, sizeof(Constant));
}

void SpaceShooterGame::UpdateModel(TMatrix world, const std::vector<MaterialPtr>& list_material)
{
	Constant cc;
	TMatrix mtemp;
	cc._world.Identity;

	//mtemp.Identity;
	//mtemp = TMatrix::CreateScale(scale);
	//cc._world *= mtemp;

	//mtemp.Identity;
	//mtemp = TMatrix::CreateRotationX(rotation.x);
	//cc._world *= mtemp;
	//mtemp.Identity;
	//mtemp = TMatrix::CreateRotationY(rotation.y);
	//cc._world *= mtemp;
	//mtemp.Identity;
	//mtemp = TMatrix::CreateRotationZ(rotation.z);
	//cc._world *= mtemp;

	//mtemp.Identity;
	//mtemp.Translation(position);
	//cc._world *= mtemp;
	cc._world = world;
	
	TVector4 temp;
	temp.x = _camera->m_vCameraPos.x; temp.y = _camera->m_vCameraPos.y; temp.z = _camera->m_vCameraPos.z; temp.w = 1.0f;

	cc._cameraPos = temp;
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	
	cc, _light_position = _light_position;
	cc._light_radius = 0.0f;
	TVector3 temp_light = _light_rot_matrix.Backward();
	cc._light_dir.x = temp_light.x; cc._light_dir.y = temp_light.y; cc._light_dir.z = temp_light.z; cc._light_dir.w = 1.0f;
	cc._cTime = _time;
	for (size_t m = 0; m < list_material.size(); m++)
	{
		list_material[m]->SetData(&cc, sizeof(Constant));
	}
}

void SpaceShooterGame::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
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

void SpaceShooterGame::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	Input::get()->Init();
	InputSystem::get()->addListener(this);

	// 카메라 생성 및 초기화
	_camera = std::make_shared<ThirdPersonCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	// 스왑체인 생성
	RECT rc = GetClientRect();
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	// 텍스쳐 로딩
	_sky_Tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/stars_map.jpg");
	spaceship_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/spaceship.jpg");
	asteroid_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/asteroid.jpg");
	// 오브젝트 로딩
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");
	spaceship_mesh_ = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/spaceship.obj");
	asteroid_mesh_ = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/asteroid.obj");
	// 머티리얼 생성
	_base_mater = MGraphicsEngine::get()->CreateMaterial(L"DirectionalLightVertex.hlsl", L"DirectionalLightPixel.hlsl");
	_base_mater->AddTexture(_sky_Tex);
	_base_mater->SetCullMode(CULL_MODE_BACK);
	spaceship_mat_ = MGraphicsEngine::get()->CreateMaterial(_base_mater);
	spaceship_mat_->AddTexture(spaceship_tex_);
	spaceship_mat_->SetCullMode(CULL_MODE_BACK);

	asteroid_mat_ = MGraphicsEngine::get()->CreateMaterial(_base_mater);
	asteroid_mat_->AddTexture(asteroid_tex_);
	asteroid_mat_->SetCullMode(CULL_MODE_BACK);
	// 스카이 박스
	_skyMat = MGraphicsEngine::get()->CreateMaterial(L"SkyBoxVertexShader.hlsl", L"SkyBoxPixelShader.hlsl");
	_skyMat->AddTexture(_sky_Tex);
	_skyMat->SetCullMode(CULL_MODE_FRONT);

	_list_materials.reserve(32);
}

void SpaceShooterGame::OnUpdate()
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
		//_light_radius -= 1.0f * Timer::get()->m_fDeltaTime;
	}
	if (Input::get()->GetKey(VK_F11) == KEY_HOLD)
	{
		//_light_radius += 1.0f * Timer::get()->m_fDeltaTime;
	}
	// 카메라 라이트 스카이 박스 업데이트
	UpdateQuadPosition();
	this->Render();
}

void SpaceShooterGame::Render()
{
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		1, 1, 1, 1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	// 우주선 렌더
	_list_materials.clear();
	_list_materials.push_back(spaceship_mat_);
	UpdateModel(space_world, _list_materials);
	DrawMesh(spaceship_mesh_, _list_materials);

	// 소행성 렌더
	_list_materials.clear();
	_list_materials.push_back(asteroid_mat_);
	TMatrix temp;
	temp.Identity;
	temp.Translation(TVector3(15, 15, 0));
	UpdateModel(temp, _list_materials);
	DrawMesh(asteroid_mesh_, _list_materials);

	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);

	// 버퍼 바꾸기
	_swapChain->Present(true);
	// 상수버퍼 시간 갱신
	_time += Timer::get()->m_fDeltaTime;
}

void SpaceShooterGame::OnDestroy()
{
	MWindow::OnDestroy();
	_swapChain->SetFullScreen(false, 1, 1);
}

void SpaceShooterGame::OnFocus()
{
	InputSystem::get()->addListener(this);
}

void SpaceShooterGame::OnKillFocus()
{
	InputSystem::get()->removeListener(this);
}
void SpaceShooterGame::OnSize()
{
	RECT rc = this->GetClientRect();
	_swapChain->Resize(rc.right, rc.bottom);
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(rc.right) / (float)(rc.bottom));
	Render();
}


void SpaceShooterGame::onKeyDown(int key)
{

}

void SpaceShooterGame::onKeyUp(int key)
{

}

void SpaceShooterGame::OnMouseMove(const Point& delta_mouse_pos)
{
}
void SpaceShooterGame::OnLeftMouseDown(const Point& delta_mouse_pos)
{
}
void SpaceShooterGame::OnLeftMouseUp(const Point& delta_mouse_pos)
{
}
void SpaceShooterGame::OnRightMouseDown(const Point& delta_mouse_pos)
{
}
void SpaceShooterGame::OnRightMouseUp(const Point& delta_mouse_pos)
{
}