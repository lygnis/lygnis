#pragma once
#include "MStd.h"
#include <vector>
#include <map>
#include "ControlUI.h"


class Sprite : public ControlUI
{
public:
	// ���̴� ���� ��θ� �޴´�.
	Sprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~Sprite();
};

