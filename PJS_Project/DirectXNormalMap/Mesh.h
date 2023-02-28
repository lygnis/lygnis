#pragma once
#include "Resource.h"
#include "MVertexBuffer.h"
#include "IndexBuffer.h"
#include <Windows.h>

struct MaterialSlot
{
	size_t start_index = 0;
	size_t num_indices = 0;
	size_t material_id = 0;
};


class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	const MVertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();

	const MaterialSlot& GetMaterialSlot(UINT slot);
	size_t GetNumMaterialSlots();
private:
	void ComputeTangents(const TVector3& v0, const TVector3& v1, const TVector3& v2,
		const TVector2& t0, const TVector2& t1, const TVector2& t2,
		TVector3& tangent,  TVector3& binormal);
private:
	MVertexBufferPtr _vertex_buffer;
	IndexBufferPtr _index_buffer;
	std::vector<MaterialSlot> _material_slots;
private:
	friend class DeviceContext;
};

