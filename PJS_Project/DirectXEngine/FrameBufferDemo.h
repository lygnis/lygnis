
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
	// ���ؽ� ���̴� �ȼ����̴��� ���� ��� ���ҽ��� ���� ��Ƽ������ �Ϻ��̴�.
	void DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material);
	void UpdateCamera();
	void UpdateThirdPersonCamera();
	void UpdateModel(TVector3 pos, TVector3 rotation, TVector3 scale, const std::vector<MaterialPtr>& list_material);
	void UpdateSkyBox();
	void UpdateLight();
	void Render();
	float lerp(float start, float end, float delta);
public:
	// MWindow��(��) ���� ��ӵ�
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
	// �ݱ��� ���� �ݰ�
	//float _light_radius = 500.0f;

	// ���� ���� ����
	float _light_tor_y;
	TMatrix _world_cam;
	TMatrix _view_cam;
	TMatrix _proj_cam;
	// ������ ����Ʈ ��ġ
	TVector4 _light_position;
	TMatrix	_light_rot_matrix;


	float cam_distance_ = 14.f;
	float current_cam_distance_;
	float forward_ = 0.0f;
	std::vector<MaterialPtr> _list_materials;
	bool _fullscreen_state = false;

	MiniGame mini_game;
};