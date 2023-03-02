
#pragma once
#include "MWindow.h"
#include "MGraphicsEngine.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Timer.h"
#include "DebugCamera.h"
#include "MiniGame.h"
class FrameBufferDemo :public MWindow
{
public:
	FrameBufferDemo() {}
	~FrameBufferDemo() {}
public:
	void UpdateQuadPosition();
	// 버텍스 셰이더 픽셀셰이더와 같은 모든 리소스가 이제 머티리얼의 일부이다.
	void DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material);
	void UpdateCamera();
	void UpdateThirdPersonCamera();
	void UpdateModel(TVector3 pos, TVector3 rotation, TVector3 scale, const std::vector<MaterialPtr>& list_material);
	void UpdateSkyBox();
	void UpdateLight();
	void Render();
	float lerp(float start, float end, float delta);
public:
	// MWindow을(를) 통해 상속됨
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;
	virtual void OnSize() override;
private:
	SwapChainPtr		_swapChain;
	TexturePtr			brick_tex_;
	MaterialPtr			brick_mat_;
	TexturePtr			 brick_normal_tex_;
	TexturePtr			_sky_Tex;

	MeshPtr				_sky_mesh;
	MeshPtr				_monitor_mesh;
	MaterialPtr			_monitor_mat;
	MaterialPtr			screen_mat_;

	MeshPtr				spehre_mesh_;
	MaterialPtr			_skyMat;

	MaterialPtr			_base_mater;

	std::shared_ptr<DebugCamera> _camera;
private:
	float _camPos = 0.0f;
	float _time = 0.0f;
	// 반구형 광원 반경
	//float _light_radius = 500.0f;

	// 빛의 빛의 각도
	float _light_tor_y;
	TMatrix _world_cam;
	TMatrix _view_cam;
	TMatrix _proj_cam;
	// 포지션 라이트 위치
	TVector4 _light_position;
	TMatrix	_light_rot_matrix;


	float cam_distance_ = 14.f;
	float current_cam_distance_;
	float forward_ = 0.0f;
	std::vector<MaterialPtr> _list_materials;
	bool _fullscreen_state = false;

	MiniGame mini_game;
};