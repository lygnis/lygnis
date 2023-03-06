#include "ResourceManager.h"

ResourceManager::ResourceManager()
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
		return it->second;

	if (!std::filesystem::exists(file_path))
		return ResourcePtr();

	if (!ext.compare(L".obj"))
	{
		//auto ptr = std::make_shared<>
	}



	return nullptr;
}

bool ResourceManager::Release()
{
	return true;
}