#include "Button.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"
Button::Button(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path) : Sprite(vertex_shader_path,  pixel_shader_path)
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
Button::Button(const ButtonPtr& button) : Sprite(button)
{

}

void Button::CoordUpdate(const TMatrix& world_mat, const TMatrix& viewport_mat)
{
	TVector3 v[4];
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&v[i], &vertices[i].position, &world_mat);
		D3DXVec3TransformCoord(&v[i], &v[i], &viewport_mat);
	}
	rect_.left = v[0].x;
	rect_.right = v[2].x;
	rect_.top = v[1].y;
	rect_.bottom = v[3].y;
}

void Button::SetState(ButtonState state)
{
	btn_state_ = state;
}

ButtonState Button::GetState()
{
	return btn_state_;
}
