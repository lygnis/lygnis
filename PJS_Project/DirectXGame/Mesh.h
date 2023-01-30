#pragma once
#include "Resource.h"
#include "MVertexBuffer.h"
#include "IndexBuffer.h"
#include <Windows.h>
class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	const MVertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();
private:
	MVertexBufferPtr _vertex_buffer;
	IndexBufferPtr _index_buffer;
private:
	friend class DeviceContext;
};

