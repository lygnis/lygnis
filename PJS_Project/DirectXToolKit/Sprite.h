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
	// ���̴� ���� ��θ� �޴´�.
	Sprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	Sprite(const SpritePtr& sprite);
	~Sprite();

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(UINT index);
	void SetRect(RECT rt, UINT tex_num_size);
	void ReCompilePixelShader(const wchar_t* pixel_shader_path);
	// ������� ������Ʈ
	void SetData(void* data, UINT size);
	// ���ؽ� �ε��� ���� ��������
	MVertexBufferPtr	GetVertexBuffer();
	IndexBufferPtr		GetIndexBuffer();
	std::vector<TexturePtr> _vec_textures;
private:
	MVertexBufferPtr vertex_buffer_;
	IndexBufferPtr index_buffer_;
	ConstantBufferPtr _constant_buffer;
	MVertexShaderPtr _vertex_shader;
	PixelShaderPtr  _pixel_shader;
private:
	friend class MGraphicsEngine;
};

