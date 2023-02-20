#pragma once
#include "Sprite.h"
enum ButtonState
{
	BTN_NORMAL,
	BTN_HOVER,
	BTN_CLICK,
	BTN_DISABLE
};
class Button : public Sprite
{
public:
	Button(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	Button(const ButtonPtr& button);
	virtual ~Button() {};
};

