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
	//Ű���� ���� ���� �ݹ� �Լ�
	virtual void onKeyDown(int key) =0;
	virtual void onKeyUp(int key) = 0;
	// ���콺 �Է� ���� ���� �ݹ�
	virtual void OnMouseMove(const Point& delta_mouse_pos) = 0;
	virtual void OnLeftMouseDown(const Point& delta_mouse_pos) = 0;
	virtual void OnLeftMouseUp(const Point& delta_mouse_pos) = 0;

	virtual void OnRightMouseDown(const Point& delta_mouse_pos) = 0;
	virtual void OnRightMouseUp(const Point& delta_mouse_pos) = 0;
};