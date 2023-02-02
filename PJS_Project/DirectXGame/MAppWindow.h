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
	void DrawMesh(const MeshPtr& mesh, MVertexShaderPtr& vs, PixelShaderPtr& ps, const ConstantBufferPtr& cb, 
		const TexturePtr* list_tex, UINT num_texture);
	void UpdateCamera();
	void UpdateModel();
	void UpdateSkyBox();
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
	MVertexBufferPtr	_vb;
	PixelShaderPtr		_ps;
	PixelShaderPtr		_sky_ps;
	MVertexShaderPtr	_vs;
	ConstantBufferPtr	_cb;
	ConstantBufferPtr	_sky_cb;
	IndexBufferPtr		_ib;
	TexturePtr			_earth_color_tex;
	TexturePtr			_earth_spec_tex;
	TexturePtr			_earth_night_tex;
	TexturePtr			_clouds_tex;
	TexturePtr			_sky_Tex;
	MeshPtr				_mesh;
	MeshPtr				_sky_mesh;
	std::shared_ptr<DebugCamera> _camera;
private:
	DWORD _oldDelta;
	DWORD _newDelta;
	float _deltaTime;

	float _deltaPos;

	float _rot_x = 0.0f;
	float _rot_y = 0.0f;
	float _camPos = 0.0f;
	float _time = 0.0f;

	float _light_tor_y;
	TMatrix _world_cam;
	TMatrix _view_cam;
	TMatrix _proj_cam;

	bool _fullscreen_state = false;
public:
	TMatrix RotationY(float fRad);
};

