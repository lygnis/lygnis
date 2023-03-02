#include "BumpMapping.h"
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



void BumpMapping::UpdateQuadPosition()
{
	UpdateThirdPersonCamera();
	UpdateLight();
	UpdateSkyBox();
}

void BumpMapping::UpdateCamera()
{
	_camera->Frame();
	_view_cam = _camera->mat_view_;
	_proj_cam = _camera->mat_proj_;
}
void BumpMapping::UpdateThirdPersonCamera()
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
void BumpMapping::UpdateLight()
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


void BumpMapping::UpdateSkyBox()
{
	// ��ī�� �ڽ� ������Ʈ
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(4000.f, 4000.f, 4000.f));
	TVector3 camWorld = _camera->camera_pos_;
	cc._world.Translation(camWorld);
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_skyMat->SetData(&cc, sizeof(Constant));
}

void BumpMapping::UpdateModel(TVector3 pos, TVector3 rotation, TVector3 scale, const std::vector<MaterialPtr>& list_material)
{
	Constant cc;
	TMatrix mtemp;
	cc._world.Identity;
	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateScale(scale);
	cc._world *= mtemp;

	mtemp =TMatrix::Identity;
	mtemp = TMatrix::CreateRotationX(rotation.x);
	cc._world *= mtemp;

	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateRotationY(rotation.y);
	cc._world *= mtemp;

	mtemp = TMatrix::Identity;
	mtemp = TMatrix::CreateRotationZ(rotation.z);
	cc._world *= mtemp;


	mtemp = TMatrix::Identity;
	mtemp.Translation(pos);
	cc._world *= mtemp;
	cc._world;

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

void BumpMapping::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
{
	// ������Ʈ ������
	// ���ؽ��� �ﰢ��
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(mesh->getVertexBuffer());
	// �ε����� �ﰢ��
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(mesh->getIndexBuffer());

	// ���� ����ϰ� �ִ� ��Ƽ������ ���⼭ �׷��� ���������ο� ���ε��Ѵ�.
	for (size_t m = 0; m < mesh->GetNumMaterialSlots(); m++)
	{
		if (m >= list_material.size())
			break;
		MaterialSlot mat = mesh->GetMaterialSlot(m);
		// ��Ƽ���� ���� ����� ����Ͽ� ��Ƽ������ �׷��� ������ ���ο� ���ε� �Ѵ�.
		MGraphicsEngine::get()->SetMaterial(list_material[m]);

		MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(mat.num_indices, 0, mat.start_index);
	}
}

void BumpMapping::OnCreate()
{
	// Ÿ�̸�
	Timer::get()->Init();
	Input::get()->Init();

	// ī�޶� ���� �� �ʱ�ȭ
	_camera = std::make_shared<DebugCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 5000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	// ����ü�� ����
	RECT rc = GetClientRect();
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	// ���� ����

	// �ؽ��� �ε�
	_sky_Tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sky.jpg");
	brick_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick_d.jpg");
	brick_normal_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick_n.jpg");
	// ������Ʈ �ε�
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");
	spehre_mesh_ = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");
	// ��Ƽ���� ����
	_base_mater = MGraphicsEngine::get()->CreateMaterial(L"DirectionalLightVertex.hlsl", L"DirectionalLightPixel.hlsl");
	_base_mater->AddTexture(_sky_Tex);
	_base_mater->SetCullMode(CULL_MODE_BACK);
	// ��ī�� �ڽ�
	_skyMat = MGraphicsEngine::get()->CreateMaterial(L"SkyBoxVertexShader.hlsl", L"SkyBoxPixelShader.hlsl");
	_skyMat->AddTexture(_sky_Tex);
	_skyMat->SetCullMode(CULL_MODE_FRONT);

	brick_mat_ = MGraphicsEngine::get()->CreateMaterial(L"DirLightBumpVS.hlsl", L"DirLightBumpPS.hlsl");
	brick_mat_->AddTexture(brick_tex_);
	brick_mat_->AddTexture(brick_normal_tex_);
	brick_mat_->SetCullMode(CULL_MODE_BACK);

	_list_materials.reserve(32);
}

void BumpMapping::OnUpdate()
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
	// ī�޶� ����Ʈ ��ī�� �ڽ� ������Ʈ
	UpdateQuadPosition();
	this->Render();
}

void BumpMapping::Render()
{
	// ������
	// ����Ÿ�� �� ����
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		0.5, 0.5, 0.5, 1);
	RECT rc = this->GetClientRect();
	// ����Ʈ ����
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	_list_materials.clear();
	_list_materials.push_back(brick_mat_);
	UpdateModel(TVector3(0,0,0), TVector3(), TVector3(1,1,1), _list_materials);
	DrawMesh(spehre_mesh_, _list_materials);


	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);
	_list_materials.clear();

	// ���� �ٲٱ�
	_swapChain->Present(true);
	// ������� �ð� ����
	_time += Timer::get()->m_fDeltaTime;
}


float BumpMapping::lerp(float start, float end, float delta)
{
	return start * (1.f - delta) + end * (delta);
}

void BumpMapping::OnDestroy()
{
	MWindow::OnDestroy();
	_swapChain->SetFullScreen(false, 1, 1);
}

void BumpMapping::OnFocus()
{
	//InputSystem::get()->addListener(this);
}

void BumpMapping::OnKillFocus()
{
	//InputSystem::get()->removeListener(this);
}
void BumpMapping::OnSize()
{
	RECT rc = this->GetClientRect();
	_swapChain->Resize(rc.right, rc.bottom);
	_camera->CreateProjMatrix(0.1f, 5000.0f, 3.141 * 0.5f, (float)(rc.right) / (float)(rc.bottom));
	UpdateQuadPosition();
	Render();
}


