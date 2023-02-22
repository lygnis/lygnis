#pragma once
#include "MStd.h"

#include <map>
class ObjectManager
{
public:
	ObjectManager() {};
	~ObjectManager() {};
public:
	SpritePtr	CreateSprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	SpritePtr	CreateSprite(const SpritePtr& sprite);
	ButtonPtr	CreateButton(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	ButtonPtr	CreateButton(const ButtonPtr& button);
	void		InsertSprite(UINT index, SpritePtr& sprite );
	void        InsertButton(UINT index, ButtonPtr& button);
	SpritePtr   GetSprite(UINT index);
	int         GetSpriteSize();
public:
	std::map<UINT, SpritePtr> sprite_list_;
	std::map<UINT, ButtonPtr> button_list_;
};

