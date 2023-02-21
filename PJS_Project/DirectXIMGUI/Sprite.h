#pragma once
#include "MStd.h"
#include <vector>
class MGraphicsEngine;
struct vertex
{
	TVector3 position;
	TVector2 texcoord;
	TVector3 normal;
	TVector4 color;
};

class Sprite
{
public:
	// 쉐이더 파일 경로를 받는다.
	Sprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	Sprite(const SpritePtr& sprite);
	~Sprite();

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(UINT index);
	void ReCompilePixelShader(const wchar_t* pixel_shader_path);
	// 상수버퍼 업데이트
	void SetData(void* data, UINT size);
	// 버텍스 인덱스 정보 가져오기
	MVertexBufferPtr	GetVertexBuffer();
	IndexBufferPtr		GetIndexBuffer();
	// 크기 조정
	void Scale(float x, float y, float z);
	TVector3 GetSclae();
	void Position(float x, float y, float z);
	TVector3 GetPosition();
	RECT	GetRect();
public:
	// 
	std::vector<TexturePtr> _vec_textures;
	// 스프라이트 크기 조정
	RECT			rect_;
	// 이름
	std::string		names_;
	// ID
	UINT			SpriteID_;
	bool			anim_loop_ = false;
	UINT			texture_index_=0;
protected:
	// 크기
	TVector3 spr_scale_;
	TVector3 spr_position_;
	vertex   vertices[4];
	MVertexBufferPtr vertex_buffer_;
	IndexBufferPtr index_buffer_;
	ConstantBufferPtr _constant_buffer;
	MVertexShaderPtr _vertex_shader;
	PixelShaderPtr  _pixel_shader;
	PixelShaderPtr  _pixel_shader_discard;


	// 텍스쳐 사이즈
	std::vector<RECT>			uv_rect_;
	std::vector<POINT>			image_size_;
	bool						recompile_shader_ = false;
private:
	friend class MGraphicsEngine;
};

