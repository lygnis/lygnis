#pragma once
#pragma once
#include "MStd.h"

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system);
	~ConstantBuffer() {};
public:
	void Update(DeviceContextPtr context, void* buffer);
private:
	ComPtr<ID3D11Buffer> _constBuffer;
	RenderSystem* _system = nullptr;
private:
	friend class DeviceContext;
};
