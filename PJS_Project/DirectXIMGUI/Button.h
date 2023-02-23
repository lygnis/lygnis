#pragma once
#include "ControlUI.h"

class Button : public ControlUI
{
public:
	Button(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	virtual ~Button() {};
public:
	//void CoordUpdate(const TMatrix& world_mat, const TMatrix& viewport_mat);
	void SetState(ButtonState state);
	ButtonState GetState();
private:
	ButtonState btn_state_;
};

