#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{

	}
	~InputListener()
	{

	}
	//키보드 순수 가상 콜백 함수
	virtual void onKeyDown(int key) =0;
	virtual void onKeyUp(int key) = 0;
	// 마우스 입력 순수 가상 콜백
	virtual void OnMouseMove(const Point& delta_mouse_pos) = 0;
	virtual void OnLeftMouseDown(const Point& delta_mouse_pos) = 0;
	virtual void OnLeftMouseUp(const Point& delta_mouse_pos) = 0;

	virtual void OnRightMouseDown(const Point& delta_mouse_pos) = 0;
	virtual void OnRightMouseUp(const Point& delta_mouse_pos) = 0;
};