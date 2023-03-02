#include "FrameBufferDemo.h"
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



void FrameBufferDemo::UpdateQuadPosition()
{
	UpdateThirdPersonCamera();
	UpdateLight();
	UpdateSkyBox();
}

void FrameBufferDemo::UpdateCamera()
{
	_camera->Frame();
	_view_cam = _camera->mat_view_;
	_proj_cam = _camera->mat_proj_;
}
void FrameBufferDemo::UpdateThirdPersonCamera()
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
void FrameBufferDemo::UpdateLight()
{
	//_light_tor_y += 1.807f * Timer::get()->m_fDeltaTime;
	TMatrix temp;
	temp.Identity;
	_light_rot_matrix = TMatrix::Identity;
	temp = TMatrix::Identity;
	temp = TMatrix::CreateRotationX(-0.707f);
	_light_rot_matrix = _light_rot_matrix*temp;
	temp = TMatrix::Identity;
	temp = TMatrix::CreateRotationY(2.14f);
	_light_rot_matrix = _light_rot_matrix*temp;
}


void FrameBufferDemo::UpdateSkyBox()
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

void FrameBufferDemo::UpdateModel(TVector3 pos, TVector3 rotation, TVector3 scale, const std::vector<MaterialPtr>& list_material)
{
	Constant cc;
	TMatrix mtemp;
	cc._world.Identity;
	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateScale(scale);
	cc._world = cc._world*mtemp;

	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateRotationX(rotation.x);
	cc._world = cc._world * mtemp;;

	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateRotationY(rotation.y);
	cc._world = cc._world * mtemp;;

	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateRotationZ(rotation.z);
	cc._world = cc._world * mtemp;;


	mtemp = TMatrix::Identity;
	mtemp.Translation(pos);
	cc._world = cc._world * mtemp;;

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

void FrameBufferDemo::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
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

void FrameBufferDemo::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	Input::get()->Init();

	// 카메라 생성 및 초기화
	_camera = std::make_shared<DebugCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 5000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	// 스왑체인 생성
	RECT rc = GetClientRect();
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	// 난수 생성

	// 텍스쳐 로딩
	_sky_Tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sky.jpg");
	brick_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick_d.jpg");
	brick_normal_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick_n.jpg");
	// 오브젝트 로딩
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");
	_monitor_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/monitor.obj");
	// 머티리얼 생성
	_base_mater = MGraphicsEngine::get()->CreateMaterial(L"DirectionalLightVertex.hlsl", L"DirectionalLightPixel.hlsl");
	_base_mater->AddTexture(_sky_Tex);
	_base_mater->SetCullMode(CULL_MODE_BACK);
	// 스카이 박스
	_skyMat = MGraphicsEngine::get()->CreateMaterial(L"SkyBoxVertexShader.hlsl", L"SkyBoxPixelShader.hlsl");
	_skyMat->AddTexture(_sky_Tex);
	_skyMat->SetCullMode(CULL_MODE_FRONT);

	_monitor_mat = MGraphicsEngine::get()->CreateMaterial(_base_mater);
	_monitor_mat->AddTexture(brick_tex_);
	_monitor_mat->SetCullMode(CULL_MODE_BACK);

	screen_mat_ = MGraphicsEngine::get()->CreateMaterial(_base_mater);
	screen_mat_->AddTexture(brick_normal_tex_);
	screen_mat_->SetCullMode(CULL_MODE_BACK);

	_list_materials.reserve(32);

	mini_game.SetWindowSize(TMath::Rect(rc.right - rc.left, rc.bottom - rc.top));
	mini_game.OnCreate();

	screen_mat_->AddTexture(mini_game.GetRenderTarget());
}

void FrameBufferDemo::OnUpdate()
{
	Timer::get()->Frame();
	Input::get()->Frame();

	mini_game.OnUpdate();
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

void FrameBufferDemo::Render()
{
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		0.5, 0.5, 0.5, 1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	_list_materials.clear();
	_list_materials.push_back(_monitor_mat);
	_list_materials.push_back(screen_mat_);
	UpdateModel(TVector3(0, 0, 0), TVector3(0, 3.14f,0), TVector3(1, 1, 1), _list_materials);
	DrawMesh(_monitor_mesh, _list_materials);


	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);
	_list_materials.clear();

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearDepthStencil(this->_swapChain);
	// 버퍼 바꾸기
	_swapChain->Present(true);
	// 상수버퍼 시간 갱신
	_time += Timer::get()->m_fDeltaTime;
}


float FrameBufferDemo::lerp(float start, float end, float delta)
{
	return start * (1.f - delta) + end * (delta);
}

void FrameBufferDemo::OnDestroy()
{
	MWindow::OnDestroy();
	_swapChain->SetFullScreen(false, 1, 1);
}

void FrameBufferDemo::OnFocus()
{
	//InputSystem::get()->addListener(this);
}

void FrameBufferDemo::OnKillFocus()
{
	//InputSystem::get()->removeListener(this);
}
void FrameBufferDemo::OnSize()
{
	RECT rc = this->GetClientRect();
	_swapChain->Resize(rc.right, rc.bottom);
	mini_game.SetWindowSize(TMath::Rect(rc.right - rc.left, rc.bottom - rc.top));

	_camera->CreateProjMatrix(0.1f, 5000.0f, 3.141 * 0.5f, (float)(rc.right) / (float)(rc.bottom));
	UpdateQuadPosition();
	Render();
}


