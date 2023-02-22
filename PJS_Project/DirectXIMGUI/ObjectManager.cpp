#include "ObjectManager.h"
#include "MGraphicsEngine.h"
#include "Button.h"

SpritePtr ObjectManager::CreateSprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	SpritePtr sprite;
	sprite = std::make_shared<Sprite>(vertex_shader_path, pixel_shader_path);
	return sprite;
}
ButtonPtr ObjectManager::CreateButton(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	ButtonPtr btn;
	btn = std::make_shared<Button>(vertex_shader_path, pixel_shader_path);
	return btn;
}

SpritePtr ObjectManager::CreateSprite(const SpritePtr& sprite)
{
	SpritePtr spr;
	spr = std::make_shared<Sprite>(sprite);
	return spr;
}
ButtonPtr ObjectManager::CreateButton(const ButtonPtr& button)
{
	ButtonPtr btn;
	btn = std::make_shared<Button>(button);
	return btn;
}

SpritePtr ObjectManager::GetSprite(UINT index)
{
	return sprite_list_[index];
}


int ObjectManager::GetSpriteSize()
{
	return sprite_list_.size();
}

void ObjectManager::InsertButton(UINT index, ButtonPtr& button)
{
	button_list_.insert(std::make_pair(index, button));
}
void ObjectManager::InsertSprite(UINT index, SpritePtr& sprite)
{
	sprite_list_.insert(std::make_pair(index, sprite));
}
