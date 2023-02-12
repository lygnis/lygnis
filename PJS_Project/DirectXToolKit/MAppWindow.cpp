#include "MAppWindow.h"
#include "MVertexBuffer.h"
#include <Windows.h>
#include "InputSystem.h"
#include "Mesh.h"
#include "Sprite.h"

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
	_view_cam = _camera->m_matView;
	_proj_cam = _camera->m_matProj;
}
void MAppWindow::UpdateLight()
{
	//_light_tor_y += 1.807f * Timer::get()->m_fDeltaTime;
	_light_position = TVector4(180,140,70,1.0f);
}

void MAppWindow::UpdateSkyBox()
{
	// ��ī�� �ڽ� ������Ʈ
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(1000.f, 1000.f, 1000.f));
	TVector3 camWorld = _camera->m_vCameraPos;
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
	temp.x = _camera->m_vCameraPos.x; temp.y = _camera->m_vCameraPos.y; temp.z = _camera->m_vCameraPos.z; temp.w = 1.0f;

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

void MAppWindow::UpdateUI(TVector3 position, SpritePtr& spr)
{
	Constant cc;
	cc._world.Identity;
	cc._world.Translation(position);
	TVector4 temp;
	temp.x = _camera->m_vCameraPos.x; temp.y = _camera->m_vCameraPos.y; temp.z = _camera->m_vCameraPos.z; temp.w = 1.0f;
	cc._cameraPos = temp;

	cc._view = _view_cam;
	cc._proj = _camera->mat_ortho_;
	cc._cTime = _time;
	spr->SetData(&cc, sizeof(Constant));
}

void MAppWindow::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
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
		MGraphicsEngine::get()->SetMaterial(list_material[m], wireframe_);
		
		MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(mat.num_indices, 0, mat.start_index);

	}
}

void MAppWindow::DrawSprite(const SpritePtr& spr)
{
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(spr->GetVertexBuffer());
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(spr->GetIndexBuffer());
	MGraphicsEngine::get()->SetSprite(spr, wireframe_);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(spr->GetIndexBuffer()->GetSizeIndexList(), 0, 0);
}

void MAppWindow::OnCreate()
{
	// Ÿ�̸�
	Timer::get()->Init();
	Input::get()->Init();
	InputSystem::get()->addListener(this);

	// ī�޶� ���� �� �ʱ�ȭ
	_camera = std::make_shared<DebugCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	RECT rc = GetClientRect();
	_camera->CreateOrthoLH((float)(this->GetClientRect().right - this->GetClientRect().left)/300, (float)(this->GetClientRect().bottom - this->GetClientRect().top)/300,0.f,10.f);
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right-rc.left,rc.bottom-rc.top);

	// �ؽ��� �ε�
	_sky_Tex =			MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sky.jpg");
	sprite_tex_ = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sand.jpg");

	test_sprite_ = MGraphicsEngine::get()->CreateSprite(L"UIVertexShader.hlsl", L"PixelShader.hlsl");
	
	// ����ü�� ����
	// ��ī�� �ڽ� �޽�
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/meshes/sphere.obj");

	// ��Ƽ���� ����
	_mater = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"PointLightShader.hlsl");
	_mater->AddTexture(_sky_Tex);
	_mater->SetCullMode(CULL_MODE_BACK);


	// ��ī�� �ڽ�
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
	if (Input::get()->GetKey('V') == KEY_UP)
		wireframe_ = !wireframe_;
	if(Input::get()->GetKey('G') == KEY_UP)
		test_sprite_->AddTexture(sprite_tex_);
	this->Render();
}

void MAppWindow::Render()
{
	// ������
	// ����Ÿ�� �� ����
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		0.2, 0.2, 0.2, 1);
	RECT rc = this->GetClientRect();
	// ����Ʈ ����
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// ī�޶� ����Ʈ ��ī�� �ڽ� ������Ʈ
	UpdateQuadPosition();
	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);

	if (!test_sprite_->_vec_textures.empty())
		test_sprite_->ReCompilePixelShader(L"SkyBoxShader.hlsl");
	UpdateUI(TVector3(0,0,0), test_sprite_);
	DrawSprite(test_sprite_);
	// ���� �ٲٱ�
	_swapChain->Present(true);
	// ������� �ð� ����
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