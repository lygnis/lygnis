#pragma once
#include "MWindow.h"
#include "MGraphicsEngine.h"
//#include "MVertexBuffer.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
//#include "Timer.h"
#include "DebugCamera.h" 
class MVertexBuffer;
class MSwapChain;

class MAppWindow :public MWindow, public InputListener
{
public:
	MAppWindow() {}
	~MAppWindow() {}
public:
	void UpdateQuadPosition();
	// 버텍스 셰이더 픽셀셰이더와 같은 모든 리소스가 이제 머티리얼의 일부이다.
	void DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material);
	void UpdateCamera();
	void UpdateModel(TVector3 position, const std::vector<MaterialPtr>& list_material);
	void UpdateSkyBox();
	void UpdateLight();
	void Render();
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
	PixelShaderPtr		_ps;
	PixelShaderPtr		_sky_ps;
	//MVertexShaderPtr	_vs;
	ConstantBufferPtr	_cb;
	ConstantBufferPtr	_sky_cb;
	//IndexBufferPtr		_ib;

	TexturePtr			_earth_color_tex;
	TexturePtr			_wall_tex;
	TexturePtr			_bricks_tex;
	TexturePtr			_earth_spec_tex;
	TexturePtr			_earth_night_tex;
	TexturePtr			_clouds_tex;
	TexturePtr			_sky_Tex;

	TexturePtr			_sand_tex;
	TexturePtr			_barrel_tex;
	TexturePtr			_brick_tex;
	TexturePtr			_window_tex;
	TexturePtr			_wood_tex;

	MeshPtr				_mesh;
	MeshPtr				_mesh_torus;
	MeshPtr				_mesh_suzanne;
	MeshPtr				_sky_mesh;
	MeshPtr				_terrain_mesh;
	MeshPtr				_house_mesh;

	MaterialPtr			_mater;
	MaterialPtr			_bricks_mat;
	MaterialPtr			_earth_mat;
	MaterialPtr			_skyMat;

	MaterialPtr			_terrain_mat;
	MaterialPtr			_barrel_mat;
	MaterialPtr			_brick_mat;
	MaterialPtr			_window_mat;
	MaterialPtr			_wood_mat;

	std::shared_ptr<DebugCamera> _camera;
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
	bool _fullscreen_state = false;
};

