#pragma once
#pragma once
#include "MStd.h"
#include "MGraphicsEngine.h"

class DeviceContext;
//class MGraphicsEngine;

class ConstantBuffer
{
public:
	ConstantBuffer() {};
	~ConstantBuffer() {};
public:
	bool Load(void* buffer, UINT size_buffer);
	void Update(DeviceContext* context, void* buffer);
	bool Release();
private:
	ComPtr<ID3D11Buffer> _constBuffer;
private:
	friend class DeviceContext;
};
