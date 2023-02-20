#pragma once
#include "MWindow.h"
#include "MGraphicsEngine.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Timer.h"
#include "ThirdPersonCamera.h" 
#include "DebugCamera.h" 

class BumpMapping :public MWindow
{
public:
	BumpMapping() {}
	~BumpMapping() {}
public:
	void UpdateQuadPosition();
	// ���ؽ� ���̴� �ȼ����̴��� ���� ��� ���ҽ��� ���� ��Ƽ������ �Ϻ��̴�.
	void DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material);
	void UpdateCamera();
	void UpdateThirdPersonCamera();
	void UpdateModel(TMatrix world, const std::vector<MaterialPtr>& list_material);
	void UpdateSkyBox();
	void UpdateLight();
	void UpdateSpaceShip();
	void Render();
	void MoveSpaceShip();
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

	TexturePtr			spaceship_tex_;
	MeshPtr				spaceship_mesh_;
	MaterialPtr			spaceship_mat_;

	TexturePtr			asteroid_tex_;
	MeshPtr				asteroid_mesh_;
	MaterialPtr			asteroid_mat_;

	TexturePtr			_sky_Tex;
	MeshPtr				_sky_mesh;
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
	// ���༺
	TVector3 asteroids_pos_[200];
	TVector3 asteroids_rot_[200];
	TVector3 asteroids_scale_[200];

	TMatrix space_world;
	TVector3 spaceship_rot_;
	TVector3 spaceship_pos_;
	TVector3 camera_rot_;
	// ���� ���ּ� ��ġ
	TVector3 current_spaceship_pos_;
	TVector3 current_spaceship_rot_;
	float spaceship_speed_ = 80.0f;
	float cam_distance_ = 14.f;
	float current_cam_distance_;
	float forward_ = 0.0f;
	std::vector<MaterialPtr> _list_materials;
	bool _fullscreen_state = false;
};