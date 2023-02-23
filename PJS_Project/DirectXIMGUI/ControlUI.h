#pragma once
#include "MStd.h"
#include <vector>
#include <map>

struct vertex
{
	TVector3 position;
	TVector2 texcoord;
	TVector3 normal;
	TVector4 color;
};
enum UI_TYPE
{
	M_SPRITE,
	M_BUTTON,
};
enum ButtonState
{
	BTN_NORMAL,
	BTN_HOVER,
	BTN_CLICK,
	BTN_DISABLE = 4
};

class ControlUI
{
public:
	// ���̴� ���� ��θ� �޴´�.
	ControlUI(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~ControlUI();

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(UINT index);
	void ReCompilePixelShader(const wchar_t* pixel_shader_path);
	// ������� ������Ʈ
	void SetData(void* data, UINT size);
	// ���ؽ� �ε��� ���� ��������
	MVertexBufferPtr	GetVertexBuffer();
	IndexBufferPtr		GetIndexBuffer();
	// ũ�� 
	void Scale(float x, float y, float z);
	TVector3 GetSclae();
	// ��ġ
	void Position(float x, float y, float z);
	TVector3 GetPosition();
	// �浹���� ����
	void CoordUpdate(const TMatrix& world_mat, const TMatrix& viewport_mat);
	// 
	void SetState(UI_TYPE ui_type);
	UI_TYPE GetState();
	void SetButtonState(ButtonState btn_state);
	RECT GetRect();
public:
	std::map<UINT, TexturePtr> list_textures_;
	// ��������Ʈ ũ�� ����
	RECT			rect_;
	// �̸�
	std::string		names_;
	// ID
	UINT			SpriteID_;
	bool			anim_loop_ = false;
	// ���� ������ �̹��� �ε���
	UINT            set_tex_index = 0;
protected:
	// UI ����
	UI_TYPE			ui_type_;
	// ��ư ����
	ButtonState		btn_type;
	// �ؽ�ó ��
	UINT			texture_counter_ = 0;
	// ũ��
	TVector3 spr_scale_;
	TVector3 spr_position_;
	// ���ؽ� ����
	vertex   vertices[4];
	// ����
	MVertexBufferPtr vertex_buffer_;
	IndexBufferPtr index_buffer_;
	ConstantBufferPtr _constant_buffer;
	// ���̴�
	MVertexShaderPtr _vertex_shader;
	PixelShaderPtr  _pixel_shader;
	PixelShaderPtr  _pixel_shader_discard;
	bool			recompile_shader_ = false;
private:
	friend class MGraphicsEngine;
};


