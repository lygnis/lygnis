#pragma once
#include "Resource.h"

class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path, ResourceManager* manager);
public:
private:
	Texture2DPtr texture_;

	friend class Material;
};

