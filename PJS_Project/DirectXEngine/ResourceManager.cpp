#include "ResourceManager.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
ResourceManager::ResourceManager(Game* game) : game_(game)
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::CreateResourceFromFileConcre(const wchar_t* file_path)
{
	// 리소스 파일 경로는 상대적
	std::filesystem::path resource_path = file_path;
	auto ext = resource_path.extension();

	auto it = _map_Resource.find(file_path);
	if (it != _map_Resource.end())
	{
		auto mat = std::dynamic_pointer_cast<Material>(it->second);
		if (mat)
		{
			return std::make_shared<Material>(resource_path.c_str(), this);
		}
		return it->second;
	}

	if (!std::filesystem::exists(file_path))
		return ResourcePtr();
	ResourcePtr res_ptr;

	if (!ext.compare(L".obj"))
	{
		res_ptr = std::make_shared<Mesh>(resource_path.c_str(), this);
	}
	else if (!ext.compare(L".jpg")|| !ext.compare(L".png")|| !ext.compare(L".bmp"))
	{
		res_ptr = std::make_shared<Texture>(resource_path.c_str(), this);
	}
	else if (!ext.compare(L".hlsl") || !ext.compare(L".fx"))
	{
		res_ptr = std::make_shared<Material>(resource_path.c_str(), this);
	}
	if (res_ptr)
	{
		_map_Resource.emplace(file_path, res_ptr);
		return res_ptr;
	}


	return nullptr;
}

Game* ResourceManager::GetGame()
{
	return game_;
}