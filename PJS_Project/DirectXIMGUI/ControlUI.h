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
	// 쉐이더 파일 경로를 받는다.
	ControlUI(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~ControlUI();

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(UINT index);
	void ReCompilePixelShader(const wchar_t* pixel_shader_path);
	// 상수버퍼 업데이트
	void SetData(void* data, UINT size);
	// 버텍스 인덱스 정보 가져오기
	MVertexBufferPtr	GetVertexBuffer();
	IndexBufferPtr		GetIndexBuffer();
	// 크기 
	void Scale(float x, float y, float z);
	TVector3 GetSclae();
	// 위치
	void Position(float x, float y, float z);
	TVector3 GetPosition();
	// 충돌영역 지정
	void CoordUpdate(const TMatrix& world_mat, const TMatrix& viewport_mat);
	// 
	void SetState(UI_TYPE ui_type);
	UI_TYPE GetState();
	void SetButtonState(ButtonState btn_state);
	RECT GetRect();
public:
	std::map<UINT, TexturePtr> list_textures_;
	// 스프라이트 크기 조정
	RECT			rect_;
	// 이름
	std::string		names_;
	// ID
	UINT			SpriteID_;
	bool			anim_loop_ = false;
	// 현재 선택한 이미지 인덱스
	UINT            set_tex_index = 0;
protected:
	// UI 종류
	UI_TYPE			ui_type_;
	// 버튼 상태
	ButtonState		btn_type;
	// 텍스처 수
	UINT			texture_counter_ = 0;
	// 크기
	TVector3 spr_scale_;
	TVector3 spr_position_;
	// 버텍스 정보
	vertex   vertices[4];
	// 버퍼
	MVertexBufferPtr vertex_buffer_;
	IndexBufferPtr index_buffer_;
	ConstantBufferPtr _constant_buffer;
	// 쉐이더
	MVertexShaderPtr _vertex_shader;
	PixelShaderPtr  _pixel_shader;
	PixelShaderPtr  _pixel_shader_discard;
	bool			recompile_shader_ = false;
private:
	friend class MGraphicsEngine;
};


