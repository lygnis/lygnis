#include "ObjectManager.h"
#include "MGraphicsEngine.h"
#include "Sprite.h"
#include "Button.h"
#include "Input.h"
__declspec(align(16))
struct ConstantUI
{
	TMatrix _world;
	TMatrix _view;
	TMatrix _proj;
	TVector4 _light_dir;
	TVector4 _cameraPos;
	TVector4 _light_position = TVector4(0, 1, 0, 0);
	float _light_radius;
	float _cTime = 0.0f;
	float discard_;
};
void ObjectManager::Initalize(const TMatrix& view_port, const TMatrix& ortho_mat)
{
	view_port_ = view_port;
	ortho_proj_ = ortho_mat;
	TVector3 vEye = TVector3(0.0f, 0.0f, -100.0f);
	TVector3 vAt = TVector3(0.0f, 0.0f, 100.0f);
	TVector3 vUp(0.0f, 1.0f, 0.0f);
	view_mat_ = TMatrix::CreateLookAt(vEye, vAt, vUp);
}
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

void ObjectManager::UpdateUI(UINT index)
{
	ConstantUI cc;
	TMatrix temp;
	temp = temp.Identity;
	cc._world.Identity;
	temp = TMatrix::CreateScale(ui_list_[index]->GetSclae());
	cc._world = cc._world * temp;
	temp = temp.Identity;
	temp.Translation(ui_list_[index]->GetPosition());
	cc._world = cc._world * temp;
	switch (ui_list_[index]->GetState())
	{
	case M_SPRITE:
	{
		break;
	}
	case M_BUTTON:
	{
		ui_list_[index]->SetButtonState(BTN_NORMAL);
		ui_list_[index]->CoordUpdate(cc._world, view_port_);
		RECT rt = ui_list_[index]->GetRect();
		if (PtInRect(&rt, Input::get()->m_pMpos))
		{
			ui_list_[index]->SetButtonState(BTN_HOVER);
			if (Input::get()->GetKey(VK_LBUTTON))
			{
				ui_list_[index]->SetButtonState(BTN_CLICK);
			}
		}
		break;
	}

	}
	cc._view = view_mat_;
	cc._proj = ortho_proj_;
	ui_list_[index]->SetData(&cc, sizeof(ConstantUI));
}
void ObjectManager::InsertUI(UINT index, ControlUIPtr& sel_ui)
{
	//sprite_list_.insert(std::make_pair(index, sprite));
	ui_list_.insert(std::make_pair(index, sel_ui));
}
