#pragma once
#include "MWindow.h"
#include "MGraphicsEngine.h"
//#include "MVertexBuffer.h"
#include "MVertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Timer.h"
class MVertexBuffer;
class MSwapChain;

class MAppWindow :public MWindow, public InputListener
{
public:
	MAppWindow() {}
	~MAppWindow() {}
public:
	void UpdateQuadPosition();
public:
	// MWindow을(를) 통해 상속됨
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;	
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;
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
	MVertexShaderPtr	_vs;
	ConstantBufferPtr	_cb;
	IndexBufferPtr		_ib;
	TexturePtr			_wood_tex;
	MeshPtr				_mesh;
private:
	DWORD _oldDelta;
	DWORD _newDelta;
	float _deltaTime;

	float _deltaPos;

	float _rot_x = 0.0f;
	float _rot_y = 0.0f;
	float _camPos = 0.0f;
};

