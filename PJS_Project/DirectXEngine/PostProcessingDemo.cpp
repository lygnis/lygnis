#include "PostProcessingDemo.h"
#include "MVertexBuffer.h"
#include <Windows.h>
#include "InputSystem.h"
#include "Mesh.h"
#include <time.h>
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



void PostProcessingDemo::UpdateQuadPosition()
{
	UpdateSpaceShip();
	UpdateThirdPersonCamera();
	UpdateLight();
	UpdateSkyBox();
}

void PostProcessingDemo::UpdateCamera()
{
	_camera->Frame();
	_view_cam = _camera->mat_view_;
	_proj_cam = _camera->mat_proj_;
}
void PostProcessingDemo::UpdateThirdPersonCamera()
{
	_camera->Frame();
	//_camera->camera_pos_ = current_spaceship_pos_;
	if (forward_)
	{
		if (forward_ > 0.f)
		{
			cam_distance_ = 16.0f;
		}
		else
		{
			cam_distance_ = 9.0f;
		}
	}
	else
	{
		cam_distance_ = 14.0f;
	}
	current_cam_distance_ = lerp(current_cam_distance_, cam_distance_, 2.f * Timer::get()->m_fDeltaTime);

	_view_cam = _camera->mat_view_;
	_proj_cam = _camera->mat_proj_;
}
void PostProcessingDemo::UpdateLight()
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

void PostProcessingDemo::UpdateSpaceShip()
{
	if (Input::get()->GetKey(VK_RBUTTON) == KEY_HOLD)
	{
		spaceship_rot_.y += Input::get()->m_pOffset.x * 0.002;
		spaceship_rot_.x += Input::get()->m_pOffset.y * 0.002;
		// X 축 회전을 통해 상하가 반전되지 않게 방지한다.
		if (spaceship_rot_.x >= 1.57f)
			spaceship_rot_.x = 1.57f;
		else if (spaceship_rot_.x <= -1.57f)
			spaceship_rot_.x = -1.57f;
	}
	MoveSpaceShip();
	space_world.Identity;
	//_camera->yaw_ = spaceship_rot_.y; _camera->pitch_ = spaceship_rot_.x; _camera->roll_ = spaceship_rot_.z;
	current_spaceship_pos_ = TVector3::Lerp(current_spaceship_pos_, spaceship_pos_, 7.f * Timer::get()->m_fDeltaTime);
	current_spaceship_rot_ = TVector3::Lerp(current_spaceship_rot_, spaceship_rot_, 3.f * Timer::get()->m_fDeltaTime);
	space_world.Translation(current_spaceship_pos_);
	TVector3 _vPos = spaceship_pos_;
	::TQuaternion qRotation;
	::D3DXQuaternionRotationYawPitchRoll(&qRotation, current_spaceship_rot_.y, current_spaceship_rot_.x, current_spaceship_rot_.z);
	::D3DXMatrixAffineTransformation(&space_world, 1.0f, NULL, &qRotation, &_vPos);
	_camera->camera_pos_ = current_spaceship_pos_ + space_world.Backward() * -cam_distance_ + space_world.Up() * 5.0f;
}

void PostProcessingDemo::UpdateSkyBox()
{
	// 스카이 박스 업데이트
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(4000.f, 4000.f, 4000.f));
	TVector3 camWorld = _camera->camera_pos_;
	cc._world.Translation(camWorld);
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_skyMat->SetData(&cc, sizeof(Constant));
}

void PostProcessingDemo::UpdateModel(TMatrix world, const std::vector<MaterialPtr>& list_material)
{
	Constant cc;
	TMatrix mtemp;
	cc._world.Identity;
	cc._world = world;

	TVector4 temp;
	temp.x = _camera->camera_pos_.x; temp.y = _camera->camera_pos_.y; temp.z = _camera->camera_pos_.z; temp.w = 1.0f;

	cc._cameraPos = temp;
	cc._view = _view_cam;
	cc._proj = _proj_cam;

	cc._light_position = _light_position;
	cc._light_radius = 0.0f;
	TVector3 temp_light = _light_rot_matrix.Backward();
	cc._light_dir.x = temp_light.x; cc._light_dir.y = temp_light.y; cc._light_dir.z = temp_light.z; cc._light_dir.w = 1.0f;
	cc._cTime = _time;
	for (size_t m = 0; m < list_material.size(); m++)
	{
		list_material[m]->SetData(&cc, sizeof(Constant));
	}
}

void PostProcessingDemo::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
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

void PostProcessingDemo::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	Input::get()->Init();

	// 카메라 생성 및 초기화
	_camera = std::make_shared<ThirdPersonCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 5000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	// 스왑체인 생성
	RECT rc = GetClientRect();
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	// 난수 생성
	srand((UINT)time(NULL));
	for (UINT i = 0; i < 200; i++)
	{
		asteroids_pos_[i] = TVector3(rand() % 4000 + (-2000), rand() % 4000 + (-2000), rand() % 4000 + (-2000));
		asteroids_rot_[i] = TVector3((rand() % 628) / 100.f, (rand() % 628) / 100.f, (rand() % 628) / 100.f);
		float scale = rand() % 10 + 1;
		asteroids_scale_[i] = TVector3(scale, scale, scale);
	}

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

	render_target_ = MGraphicsEngine::get()->getTextureManager()->CreateTuexture(TMath::Rect(rc.right - rc.left, rc.bottom - rc.top), Texture::Type::RENDERTARGET);
	depth_stencil_ = MGraphicsEngine::get()->getTextureManager()->CreateTuexture(TMath::Rect(rc.right - rc.left, rc.bottom - rc.top), Texture::Type::DEPTHSTECIL);


}

void PostProcessingDemo::OnUpdate()
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

void PostProcessingDemo::Render()
{
	// 렌더링
	// 렌더타겟 색 설정
	
	// 렌더타겟
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->render_target_,
		0.5f, 0.5f, 0.5f, 1);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearDepthStencil(this->depth_stencil_);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetRenderTarget(this->render_target_, this->depth_stencil_);

	TMath::Rect viewport_size = render_target_->GetSize();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(viewport_size.width, viewport_size.height);


	// 우주선 렌더
	_list_materials.clear();
	_list_materials.push_back(spaceship_mat_);
	UpdateModel(space_world, _list_materials);
	DrawMesh(spaceship_mesh_, _list_materials);

	_list_materials.clear();
	_list_materials.push_back(asteroid_mat_);

	// 소행성 렌더
	for (UINT i = 0; i < 200; i++)
	{
		TMatrix temp, worldpos;
		temp.Identity;
		worldpos.Identity;
		temp = TMatrix::CreateScale(asteroids_scale_[i]);
		worldpos = worldpos * temp;
		temp.Identity;
		temp = TMatrix::CreateRotationX(asteroids_rot_[i].x);
		worldpos = worldpos * temp;
		temp.Identity;
		temp = TMatrix::CreateRotationY(asteroids_rot_[i].y);
		worldpos = worldpos * temp;
		temp.Identity;
		temp = TMatrix::CreateRotationZ(asteroids_rot_[i].z);
		worldpos = worldpos * temp;
		temp.Translation(asteroids_pos_[i]);
		worldpos = worldpos * temp;
		UpdateModel(worldpos, _list_materials);
		DrawMesh(asteroid_mesh_, _list_materials);
	}

	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		1, 1, 1, 1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 버퍼 바꾸기
	_swapChain->Present(true);
	// 상수버퍼 시간 갱신
	_time += Timer::get()->m_fDeltaTime;
}

void PostProcessingDemo::MoveSpaceShip()
{
	if (Input::get()->GetKey('W') == KEY_HOLD)
	{
		TBASIS_EX::TVector3 _v = space_world.Backward() * spaceship_speed_ * Timer::get()->m_fDeltaTime;
		spaceship_pos_ += _v;
	}
	if (Input::get()->GetKey('S') == KEY_HOLD)
	{
		TBASIS_EX::TVector3 _v = space_world.Backward() * spaceship_speed_ * Timer::get()->m_fDeltaTime;
		spaceship_pos_ -= _v;
	}
	if (Input::get()->GetKey('D') == KEY_HOLD)
	{
		TBASIS_EX::TVector3 _v = space_world.Right() * spaceship_speed_ * Timer::get()->m_fDeltaTime;
		spaceship_pos_ += _v;
	}
	if (Input::get()->GetKey('A') == KEY_HOLD)
	{
		TBASIS_EX::TVector3 _v = space_world.Right() * spaceship_speed_ * Timer::get()->m_fDeltaTime;
		spaceship_pos_ -= _v;
	}
}

float PostProcessingDemo::lerp(float start, float end, float delta)
{
	return start * (1.f - delta) + end * (delta);
}

void PostProcessingDemo::OnDestroy()
{
	MWindow::OnDestroy();
	_swapChain->SetFullScreen(false, 1, 1);
}

void PostProcessingDemo::OnFocus()
{
	//InputSystem::get()->addListener(this);
}

void PostProcessingDemo::OnKillFocus()
{
	//InputSystem::get()->removeListener(this);
}
void PostProcessingDemo::OnSize()
{
	RECT rc = this->GetClientRect();
	_swapChain->Resize(rc.right, rc.bottom);
	_camera->CreateProjMatrix(0.1f, 5000.0f, 3.141 * 0.5f, (float)(rc.right) / (float)(rc.bottom));
	UpdateQuadPosition();
	Render();
}


