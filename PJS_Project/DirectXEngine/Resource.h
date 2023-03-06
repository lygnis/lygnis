#pragma once
#include "MStd.h"
#include <string>
class Resource
{
public:
	Resource(const wchar_t* full_path, ResourceManager* manager);
	virtual ~Resource() {};
protected:
	std::wstring _full_path;
	ResourceManager* manager_ = nullptr;
};

