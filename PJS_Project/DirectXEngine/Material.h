#pragma once
#include "Resource.h"
#include <vector>
enum CULL_MODE
{
	// �ﰢ���� ���� �Ǵ� �ĸ��� �ø� �Ѵ�.(�ȿ���, �ۿ��� ������)
	CULL_MODE_FRONT = 0,
	CULL_MODE_BACK
};
class MGraphicsEngine;

class Material :public Resource
{
public:
	// ���̴� ���� ��θ� �޴´�.
	Material(const wchar_t* path, ResourceManager* manager);
	Material(const MaterialPtr& material, ResourceManager* manager);

	void AddTexture(const TexturePtr& texture);
	void RemoveTexture(UINT index);

	void SetData(void* data, UINT size);

	void SetCullMode(CULL_MODE mode);
	CULL_MODE GetCullMode();
private:
	MVertexShaderPtr _vertex_shader;
	PixelShaderPtr  _pixel_shader;
	ConstantBufferPtr _constant_buffer;
	std::vector<Texture2DPtr> _vec_textures;
	CULL_MODE _cullmode = CULL_MODE_BACK;
private:
	friend class MGraphicsEngine;
};

