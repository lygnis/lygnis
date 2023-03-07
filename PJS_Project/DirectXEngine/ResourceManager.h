#pragma once
#include <unordered_map>
#include <string>
#include "MStd.h"
#include <filesystem>
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager(Game* game);
	~ResourceManager();

	template<typename T>
	std::shared_ptr<T> CreateResourceFromFile(const wchar_t* file_path)
	{
		return std::dynamic_pointer_cast<T>(CreateResourceFromFileConcre(file_path));
	}

	Game* GetGame();
private:
	ResourcePtr CreateResourceFromFileConcre(const wchar_t* file_path);
private:
	std::unordered_map<std::wstring, ResourcePtr> _map_Resource;
	Game* game_ = nullptr;
};

