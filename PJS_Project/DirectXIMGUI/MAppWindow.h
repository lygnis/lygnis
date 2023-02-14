#pragma once
#include "MWindow.h"
#include "MGraphicsEngine.h"
#include "InputListener.h"
#include "DebugCamera.h" 
#include "ImGuiManager.h"


class MAppWindow :public MWindow, public InputListener
{
public:
	MAppWindow() {}
	~MAppWindow();
public:
	void UpdateQuadPosition();
	// 버텍스 셰이더 픽셀셰이더와 같은 모든 리소스가 이제 머티리얼의 일부이다.
	void DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material);
	void DrawSprite(const SpritePtr& spr);
	void UpdateCamera();
	void UpdateModel(TVector3 position, const std::vector<MaterialPtr>& list_material);
	void UpdateUI(TVector3 position, SpritePtr& spr);
	void UpdateSkyBox();
	void UpdateLight();
	void Render();
	void ImGuiStuff();
public:
	// MWindow을(를) 통해 상속됨
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;	
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;
	virtual void OnSize() override;
	// InputListener을(를) 통해 상속됨
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void OnMouseMove(const Point& delta_mouse_pos)override;

	virtual void OnLeftMouseDown(const Point& delta_mouse_pos) override;
	virtual void OnLeftMouseUp(const Point& delta_mouse_pos) override;

	virtual void OnRightMouseDown(const Point& delta_mouse_pos)override;
	virtual void OnRightMouseUp(const Point& delta_mouse_pos) override;
private:
	SwapChainPtr		_swapChain;
	//MVertexBufferPtr	_vb;


	TexturePtr			_sky_Tex;
	TexturePtr			sprite_tex_;
	TexturePtr			sprite_tex1_;
	TexturePtr			sprite_tex2_;

	MeshPtr				_sky_mesh;
	SpritePtr			test_sprite_;


	MaterialPtr			_mater;
	MaterialPtr			_bricks_mat;
	MaterialPtr			_earth_mat;
	MaterialPtr			_skyMat;

	std::shared_ptr<DebugCamera> _camera;
	ImGuiManager imgui_;
private:
	float _camPos = 0.0f;
	float _time = 0.0f;
	float _light_radius = 500.0f;

	float _light_tor_y;
	TMatrix _world_cam;
	TMatrix _view_cam;
	TMatrix _proj_cam;
	TVector4 _light_position;

	std::vector<MaterialPtr> _list_materials;
	std::vector<TexturePtr>	list_texture_;
	bool _fullscreen_state = false;
	bool wireframe_ = false;
	UINT tex_count_;
};

