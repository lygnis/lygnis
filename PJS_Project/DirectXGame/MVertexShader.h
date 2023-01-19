#pragma once
class MVertexShader
{
public:
	MVertexShader() {};
	~MVertexShader() {};
	bool Release() {};
private:
	bool Init(void* shader_byte_code, size_t byte_code_size);
private:
	ComPtr<ID3D11VertexShader> _vs;
};

