#pragma once
#include "MStd.h"
#include "MGraphicsEngine.h"

class DeviceContext;
//class MGraphicsEngine;

class MVertexBuffer
{
public:
	MVertexBuffer() {};
	~MVertexBuffer() {};
public:
	bool Load(void* list_vertices, UINT size_vertex, UINT size_list,void* shader_byte_code, UINT size_byte_shader);
	UINT GetSizeVertexList();
	bool Release();
private:
	UINT _size_vertex;
	UINT _size_list;
private:
	ComPtr<ID3D11Buffer> _buffer;
	ComPtr<ID3D11InputLayout> _layout;
private:
	friend class DeviceContext;
};

