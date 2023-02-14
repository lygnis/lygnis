#pragma once
#include "MVertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include <vector>
enum CULL_MODE
{
	// 삼각형의 전면 또는 후면을 컬링 한다.(안에서, 밖에서 렌더링)
	CULL_MODE_FRONT = 0,
	CULL_MODE_BACK
};
class MGraphicsEngine;

class Material
{
public:
	// 쉐이더 파일 경로를 받는다.
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

