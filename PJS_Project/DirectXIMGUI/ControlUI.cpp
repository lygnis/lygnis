#include "ControlUI.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"

ControlUI::ControlUI(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path)
{
	TVector3 position_list[] =
	{
		{ TVector3(-1.0f,-1.0f,-1.0f)},
		{ TVector3(-1.f,1.0f,-1.0f) },
		{ TVector3(1.f,1.f,-1.f) },
		{ TVector3(1.f,-1.f,-1.f)},
	};
	TVector2 texcoord_list[] =
	{
		{ TVector2(0.0f,0.0f) },
		{ TVector2(0.0f,1.0f) },
		{ TVector2(1.0f,0.0f) },
		{ TVector2(1.0f,1.0f) },
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
	vertices[0] = vertex_list[0];
	vertices[1] = vertex_list[1];
	vertices[2] = vertex_list[2];
	vertices[3] = vertex_list[3];
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
		throw std::runtime_error("Sprite not created successfully");
	vertex_buffer_ = MGraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, (UINT)size_shader);


	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, 
		"mainps", &shader_byte_code, &size_shader);
	_pixel_shader = MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);

	if (!_pixel_shader)
		throw std::runtime_error("Sprite not created successfully");
	//MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "mainps_discard", &shader_byte_code, &size_shader);
	//_pixel_shader_discard = MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	//if (!_pixel_shader_discard)
	// throw std::runtime_error("Material not created successfully");
	index_buffer_ = MGraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer(index_list, size_index_list);
	names_ = "Sprite1";
}

ControlUI::~ControlUI()
{
}

void ControlUI::AddTexture(const TexturePtr& texture)
{
	list_textures_.insert(std::make_pair(texture_counter_, texture));
	texture_counter_++;
	if (!list_textures_.empty())
	{
		recompile_shader_ = true;
		if (recompile_shader_)
		{
			ReCompilePixelShader(L"UIPixelShader.hlsl");
			recompile_shader_ = false;
		}
	}
}

void ControlUI::RemoveTexture(UINT index)
{
	if (index >= this->list_textures_.size())
		return;
	list_textures_.erase(index);
}


void ControlUI::ReCompilePixelShader(const wchar_t* pixel_shader_path)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "mainps", &shader_byte_code, &size_shader);
	_pixel_shader = std::move(MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader));

	if (!_pixel_shader)
		throw std::runtime_error("Material not created successfully");
	MGraphicsEngine::get()->getRenderSystem()->CompilePixelShader(pixel_shader_path, "ps_testing", &shader_byte_code, &size_shader);
	_pixel_shader_discard = MGraphicsEngine::get()->getRenderSystem()->CreatePixelShader(shader_byte_code, size_shader);
	if (!_pixel_shader)
		throw std::runtime_error("Material not created successfully");
}

void ControlUI::SetData(void* data, UINT size)
{

	if (!_constant_buffer)
		_constant_buffer = MGraphicsEngine::get()->getRenderSystem()->CreateConstantBuffer(data, size);
	else
	{
		_constant_buffer->Update(MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), data);
	}
}

void ControlUI::CoordUpdate(const TMatrix& world_mat, const TMatrix& viewport_mat)
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

void ControlUI::SetState(UI_TYPE ui_type)
{
	ui_type_ = ui_type;
}

UI_TYPE ControlUI::GetState()
{
	return ui_type_;
}

void ControlUI::SetButtonState(ButtonState btn_state)
{
	btn_type_ = btn_state;
}

ButtonState ControlUI::GetButtonState()
{
	return btn_type_;
}

RECT ControlUI::GetRect()
{
	return rect_;
}

MVertexBufferPtr ControlUI::GetVertexBuffer()
{
	return vertex_buffer_;
}

IndexBufferPtr ControlUI::GetIndexBuffer()
{
	return index_buffer_;
}

void ControlUI::Scale(float x, float y, float z)
{
	spr_scale_.x += x;
	spr_scale_.y += y;
	spr_scale_.z += z;
}

TVector3 ControlUI::GetSclae()
{
	return spr_scale_;
}

void ControlUI::Position(float x, float y, float z)
{
	spr_position_.x = x;
	spr_position_.y = y;
	spr_position_.z = z;
}

TVector3 ControlUI::GetPosition()
{
	return spr_position_;
}

