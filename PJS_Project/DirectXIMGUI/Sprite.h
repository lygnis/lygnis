#pragma once
#include "MStd.h"
#include <vector>
#include <map>
#include "ControlUI.h"


class Sprite : public ControlUI
{
public:
	// 쉐이더 파일 경로를 받는다.
	Sprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~Sprite();
};

