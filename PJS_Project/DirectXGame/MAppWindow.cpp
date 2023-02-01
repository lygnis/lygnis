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
};



void MAppWindow::UpdateQuadPosition()
{
	UpdateCamera();
	UpdateModel();
	UpdateSkyBox();
}

void MAppWindow::UpdateCamera()
{
	_camera->Frame();
	_view_cam = _camera->m_matView;
	_proj_cam = _camera->m_matProj;
}

void MAppWindow::UpdateModel()
{
	Constant cc;
	cc._world.Identity;
	TMatrix _light_rot_mat;
	_light_rot_mat.Identity;
	_light_rot_mat = TMatrix::CreateRotationY(_light_tor_y);
	_light_tor_y += 0.707f * Timer::get()->m_fDeltaTime;

	TVector3 temp_light = _light_rot_mat.Backward();
	cc._light_dir.x = temp_light.x; cc._light_dir.y = temp_light.y; cc._light_dir.z = temp_light.z; cc._light_dir.w = 1.0f;
	TVector4 temp;
	temp.x = _camera->m_vCameraPos.x; temp.y = _camera->m_vCameraPos.y; temp.z = _camera->m_vCameraPos.z; temp.w = 1.0f;

	cc._cameraPos = temp;
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_cb->Update(MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
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
	_sky_cb->Update(MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void MAppWindow::DrawMesh(const MeshPtr& mesh, MVertexShaderPtr& vs, PixelShaderPtr& ps, const ConstantBufferPtr& cb, const TexturePtr& texture)
{
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(vs, cb);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetConstantBuffer(ps, cb);
	// 쉐이더 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexShader(vs);
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetPixelShader(ps);

	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetTexture(ps, texture);
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

	_wood_tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/brick.png");
	_sky_Tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sky.jpg");

	_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/suzanne.obj");
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/Meshes/sphere.obj");

	RECT rc = GetClientRect();

	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right-rc.left,rc.bottom-rc.top);

	// 쉐이더 컴파일
	void* shader_byte_code = nullptr;
	size_t size_shader =0;
	MGraphicsEngine::get()->getRenderSystem()->CompileVertexShader(L"VertexShader.hlsl", "mainvs", &shader_byte_code, &size_shader);
	_vs = std::move(MGraphicsEngine::get()->getRenderSystem()->CreateVertexShader(shader_byte_code, size_shader));

	//_vb = MGraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(L"PixelShader.hlsl", "mainps", &shader_byte_code, &size_shader);
	_ps = std::move(MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader));

	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(L"SkyBoxShader.hlsl", "mainps", &shader_byte_code, &size_shader);
	_sky_ps = std::move(MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader));

	Constant cc;
	// 상수버퍼 클래스 할당
	_cb = MGraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(&cc, sizeof(Constant));
	_sky_cb = MGraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(&cc, sizeof(Constant));
}

void MAppWindow::OnUpdate()
{
	Timer::get()->Frame();
	Input::get()->Frame();
	//MAppWindow::OnUpdate();
	// 
	InputSystem::get()->Update();
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		0.2,0.2,0.2,1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	// 상수버퍼 수정 후 업데이트
	UpdateQuadPosition();
	// 렌더 .모델링
	// 밖에서 렌더링
	MGraphicsEngine::get()->getRenderSystem()->SetRaterizerState(false);
	DrawMesh(_mesh, _vs, _ps, _cb, _wood_tex);
	// 스카이 박스 그리기
	// 안쪽에서도 렌더링
	MGraphicsEngine::get()->getRenderSystem()->SetRaterizerState(true);
	DrawMesh(_sky_mesh, _vs, _sky_ps, _sky_cb, _sky_Tex);

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
void MAppWindow::OnSize()
{
	RECT rc = this->GetClientRect();
	_swapChain->Resize(rc.right, rc.bottom);
	OnUpdate();
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
