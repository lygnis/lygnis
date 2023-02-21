#include "Button.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"
Button::Button(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path) : Sprite(vertex_shader_path,  pixel_shader_path)
{
	_vec_textures.resize(4);
	btn_state_ = BTN_NORMAL;
	_vec_textures[0] = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_nor.bmp");
	_vec_textures[1] = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_pus.bmp");
	_vec_textures[2] = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_sel.bmp");
	_vec_textures[3] = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/png/main_start_dis.bmp");
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
