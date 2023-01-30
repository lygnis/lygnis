#pragma once
#include "MStd.h"


class MVertexBuffer
{
public:
	MVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader ,RenderSystem* system);
	~MVertexBuffer() {};
public:
	UINT GetSizeVertexList();
private:
	UINT _size_vertex;
	UINT _size_list;
private:
	RenderSystem* _system = nullptr;
private:
	ComPtr<ID3D11Buffer> _buffer;
	ComPtr<ID3D11InputLayout> _layout;
private:
	friend class DeviceContext;
};

