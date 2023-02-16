#include "Sprite.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"

Sprite::Sprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	TVector3 position_list[] =
	{
		{ TVector3(-0.5f,-0.5f,-0.5f)},
		{ TVector3(-0.5f,0.5f,-0.5f) },
		{ TVector3(0.5f,0.5f,-0.5f) },
		{ TVector3(0.5f,-0.5f,-0.5f)},
	};
	TVector2 texcoord_list[] =
	{
		{ TVector2(0.0f,0.0f) },
		{ TVector2(0.0f,1.0f) },
		{ TVector2(1.0f,0.0f) },
		{ TVector2(1.0f,1.0f) }
	};
	TVector4 color_list[] =
	{
		{ TVector4(1.0f,1.0f,1.0f,1.0f) }
	};
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ position_list[0],texcoord_list[1], TVector3(0,0,0),  color_list[0] },
		{ position_list[1],texcoord_list[0],TVector3(0,0,0),  color_list[0] },
		{ position_list[2],texcoord_list[2],TVector3(0,0,0),  color_list[0] },
		{ position_list[3],texcoord_list[3],TVector3(0,0,0),  color_list[0] },
	};
	UINT size_list = ARRAYSIZE(vertex_list);
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
	};
	UINT size_index_list = ARRAYSIZE(index_list);
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	MGraphicsEngine::get()->getRenderSystem()->CompileVertexShader(vertex_shader_path, "mainvs", &shader_byte_code, &size_shader);
	_vertex_shader = MGraphicsEngine::get()->getRenderSystem()->CreateVertexShader(shader_byte_code, size_shader);

	if (!_vertex_shader)
		throw std::runtime_error("Material not created successfully");
	vertex_buffer_ = MGraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, (UINT)size_shader);


	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "mainps", &shader_byte_code, &size_shader);
	_pixel_shader = MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);

	if (!_pixel_shader)
		throw std::runtime_error("Material not created successfully");
	//MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "mainps_discard", &shader_byte_code, &size_shader);
	//_pixel_shader_discard = MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	//if (!_pixel_shader_discard)
	// throw std::runtime_error("Material not created successfully");
	index_buffer_ = MGraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer(index_list, size_index_list);
	names_ = "Sprite1";
}

Sprite::Sprite(const SpritePtr& sprite)
{
	_vertex_shader = sprite->_vertex_shader;
	_pixel_shader = sprite->_pixel_shader;
}

Sprite::~Sprite()
{
}

void Sprite::AddTexture(const TexturePtr& texture)
{
	_vec_textures.push_back(texture);
	if (!_vec_textures.empty())
	{
		recompile_shader_ = true;
		if (recompile_shader_)
		{
			ReCompilePixelShader(L"SkyBoxShader.hlsl");
			recompile_shader_ = false;
		}
	}
}

void Sprite::RemoveTexture(UINT index)
{
	if (index >= this->_vec_textures.size())
		return;
	_vec_textures.erase(_vec_textures.begin() + index);
}

void Sprite::SetRect(RECT rt, UINT tex_num_size)
{
	// 스프라이트 크기 초기화 및 텍스쳐 크기
	sprite_rect_ = rt;
	image_size_.resize(tex_num_size);
	uv_rect_.resize(tex_num_size);

	for (int i = 0; i < tex_num_size; i++)
	{
		image_size_[i].x=_vec_textures[i]->GetImageDesc().Width;
		image_size_[i].y=_vec_textures[i]->GetImageDesc().Height;
		uv_rect_[i].left = sprite_rect_.left / image_size_[i].x;
		uv_rect_[i].top = sprite_rect_.top / image_size_[i].y;
	}
}

void Sprite::ReCompilePixelShader(const wchar_t* pixel_shader_path)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "mainps", &shader_byte_code, &size_shader);
	_pixel_shader = std::move(MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader));

	if (!_pixel_shader)
		throw std::runtime_error("Material not created successfully");
}

void Sprite::SetData(void* data, UINT size)
{

	if (!_constant_buffer)
		_constant_buffer = MGraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(data, size);
	else
	{
		_constant_buffer->Update(MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), data);
	}
	/*MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->GetDeviceContext()->UpdateSubresource(vertex_buffer_->_buffer.Get(),
		NULL,NULL,&data,0,0 );*/
}

MVertexBufferPtr Sprite::GetVertexBuffer()
{
	return vertex_buffer_;
}

IndexBufferPtr Sprite::GetIndexBuffer()
{
	return index_buffer_;
}

void Sprite::Scale(float x, float y, float z)
{
	spr_scale_.x += x;
	spr_scale_.y += y;
	spr_scale_.z += z;
}

TVector3 Sprite::GetSclae()
{
	return spr_scale_;
}

void Sprite::Position(float x, float y, float z)
{
	spr_position_.x = x;
	spr_position_.y = y;
	spr_position_.z = z;
}

TVector3 Sprite::GetPosition()
{
	return spr_position_;
}
