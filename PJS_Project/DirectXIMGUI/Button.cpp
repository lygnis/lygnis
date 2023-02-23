#include "Button.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"
Button::Button(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path) : ControlUI(vertex_shader_path,  pixel_shader_path)
{
	btn_state_ = BTN_NORMAL;
	TexturePtr tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_nor.bmp");
	list_textures_.insert(std::make_pair(0, tex));
	tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_pus.bmp");
	list_textures_.insert(std::make_pair(1, tex));
	tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_sel.bmp");
	list_textures_.insert(std::make_pair(2, tex));
	tex = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_dis.bmp");
	list_textures_.insert(std::make_pair(3, tex));
}


void Button::SetState(ButtonState state)
{
	btn_state_ = state;
}

ButtonState Button::GetState()
{
	return btn_state_;
}
