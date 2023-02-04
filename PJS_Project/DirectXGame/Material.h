#pragma once
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include <vector>
enum CULL_MODE
{
	// �ﰢ���� ���� �Ǵ� �ĸ��� �ø� �Ѵ�.(�ȿ���, �ۿ��� ������)
	CULL_MODE_FRONT = 0,
	CULL_MODE_BACK
};
class MGraphicsEngine;

class Material
{
public:
	// ���̴� ���� ��θ� �޴´�.
	Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	Material(const MaterialPtr& material);
	~Material();

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(UINT index);

	void SetData(void* data, UINT size);

	void SetCullMode(CULL_MODE mode);
	CULL_MODE GetCullMode();
private:
	MVertexShaderPtr _vertex_shader;
	PixelShaderPtr  _pixel_shader;
	ConstantBufferPtr _constant_buffer;
	std::vector<TexturePtr> _vec_textures;
	CULL_MODE _cullmode = CULL_MODE_BACK;
private:
	friend class MGraphicsEngine;
};

