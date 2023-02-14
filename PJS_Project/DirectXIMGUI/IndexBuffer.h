#pragma once
#include "MStd.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list ,RenderSystem* system);
	~IndexBuffer() {};
public:
	// 인덱스버퍼는 포인터와 크기만 있으면 된다.
	UINT GetSizeIndexList();
private:
	UINT _size_list;
private:
	ComPtr<ID3D11Buffer> _buffer;
	RenderSystem* _system = nullptr;
private:
	friend class DeviceContext;
};

