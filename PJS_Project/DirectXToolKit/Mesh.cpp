#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <locale>
//#include <codecvt>
//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "MGraphicsEngine.h"
#include "VertexMesh.h"
Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	// 경고 및 에러
	std::string warn;
	std::string err;

	// 유니코드를 지원안하기 때문에 ASCII 코드로 변환한다.
	std::wstring ws(full_path);
	std::string str(ws.begin(), ws.end());

	// obj 파일이 있는 동일한 경로를 사용한다.
	// mtl 파일을 찾는다.
	std::string mtldir = str.substr(0, str.find_last_of("\\/"));

	bool hr = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, str.c_str(), mtldir.c_str());
	if (!err.empty())
	{
		assert(false);
		throw std::exception("Mesh not Created Success");
	}

	if (!hr)
	{
		assert(false);
	}

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	size_t size_vertex_index_lists = 0;
	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_vertex_index_lists += shapes[s].mesh.indices.size();
	}
	list_vertices.reserve(size_vertex_index_lists);
	list_indices.reserve(size_vertex_index_lists);


	_material_slots.resize(materials.size());
	size_t index_globaloffset = 0;

	for (size_t m = 0; m < materials.size(); m++)
	{
		_material_slots[m].start_index = index_globaloffset;
		_material_slots[m].material_id = m;

		for (size_t s = 0; s < shapes.size(); s++)
		{
			size_t index_offset = 0;
			

			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				if (shapes[s].mesh.material_ids[f] != m)
				{
					unsigned char num_face_vertex = shapes[s].mesh.num_face_vertices[f];

					continue;
				}
				unsigned char num_face_vertex = shapes[s].mesh.num_face_vertices[f];
				for (unsigned char v = 0; v < num_face_vertex; v++)
				{
					// 정점 좌표
					tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
					tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
					tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];
					// 텍스트 좌표
					tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];
					// 노말 좌표
					tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
					tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
					tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

					VertexMesh vertex(TVector3(vx, vy, vz), TVector2(tx, ty), TVector3(nx, ny, nz));
					list_vertices.push_back(vertex);

					list_indices.push_back((UINT)index_globaloffset + v);
				}
				index_offset += num_face_vertex;
				index_globaloffset += num_face_vertex;
			}
		}
		_material_slots[m].num_indices = index_globaloffset - _material_slots[m].start_index;

	}
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	MGraphicsEngine::get()->GetVertexMeshLayoutShader(&shader_byte_code, &size_shader);
	_vertex_buffer = MGraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(&list_vertices[0], sizeof(VertexMesh), (UINT)list_vertices.size(),
		shader_byte_code, (UINT)size_shader);

	_index_buffer = MGraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer(&list_indices[0], (UINT)list_indices.size());
}

Mesh::~Mesh()
{
}

const MVertexBufferPtr& Mesh::getVertexBuffer()
{
	return _vertex_buffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return _index_buffer;
}

const MaterialSlot& Mesh::GetMaterialSlot(UINT slot)
{
	if (slot >= _material_slots.size())
	{
		return MaterialSlot();
	}
	return _material_slots[slot];
}

size_t Mesh::GetNumMaterialSlots()
{
	return _material_slots.size();
}

