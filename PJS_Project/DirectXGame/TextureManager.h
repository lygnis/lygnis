#pragma once
#include "ResourceManager.h"
class TextureManager : public ResourceManager
{
public:
	TextureManager();
	virtual~TextureManager();
	bool Release();
public:
	TexturePtr CreateTuextureFromeFile(const wchar_t* file_path);
protected:
	virtual Resource* CreateResourceFromFileConcre(const wchar_t* file_path);

};

