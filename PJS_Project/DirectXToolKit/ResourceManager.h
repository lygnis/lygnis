#pragma once
#include <unordered_map>
#include <string>
#include "MStd.h"
#include <filesystem>


class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();
public:
	ResourcePtr CreateResourceFromFile(const wchar_t* file_path);
	bool Release();
protected:
	virtual Resource* CreateResourceFromFileConcre(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr> _map_Resource;
};

