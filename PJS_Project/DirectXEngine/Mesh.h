#pragma once
#include "Resource.h"
#include "MVertexBuffer.h"
#include "IndexBuffer.h"
#include <Windows.h>
#include "VertexMesh.h"
struct MaterialSlot
{
	size_t start_index = 0;
	size_t num_indices = 0;
	size_t material_id = 0;
};


class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path, ResourceManager* manager);

	Mesh(VertexMesh* vertex_list_data, UINT vertex_list_size, UINT* index_list_data, UINT index_list_size, 
		MaterialSlot* material_slot_list, UINT material_slot_list_size, ResourceManager* manager);
	~Mesh();
public:
	MaterialSlot GetMaterialSlot(UINT slot);
	size_t GetNumMaterialSlots();
private:
	// 노말맵 접선벡터 공간 변환과정
	void ComputeTangents(const TVector3& v0, const TVector3& v1, const TVector3& v2,
		const TVector2& t0, const TVector2& t1, const TVector2& t2,
		TVector3& tangent,  TVector3& binormal);
private:
	MVertexBufferPtr _vertex_buffer;
	IndexBufferPtr _index_buffer;
	std::vector<MaterialSlot> _material_slots;
private:
	friend class MGraphicsEngine;
};

