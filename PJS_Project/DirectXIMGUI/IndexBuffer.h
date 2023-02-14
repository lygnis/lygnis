#pragma once
#include "MStd.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_list ,RenderSystem* system);
	~IndexBuffer() {};
public:
	// �ε������۴� �����Ϳ� ũ�⸸ ������ �ȴ�.
	UINT GetSizeIndexList();
private:
	UINT _size_list;
private:
	ComPtr<ID3D11Buffer> _buffer;
	RenderSystem* _system = nullptr;
private:
	friend class DeviceContext;
};

