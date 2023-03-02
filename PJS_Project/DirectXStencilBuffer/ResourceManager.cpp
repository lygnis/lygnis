#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

ResourcePtr ResourceManager::CreateResourceFromFile(const wchar_t* file_path)
{
	// 리소스 파일 경로는 상대적
	std::wstring full_path  = std::filesystem::path { file_path };
	auto it = _map_Resource.find(full_path);
	if (it != _map_Resource.end())
		return it->second;

	Resource* raw_res = this->CreateResourceFromFileConcre(full_path.c_str());

	if (raw_res)
	{
		ResourcePtr res(raw_res);
		_map_Resource[full_path] = res;
		return res;
	}

	return nullptr;
}

bool ResourceManager::Release()
{
	return true;
}