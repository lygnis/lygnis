#pragma once
#include "ResourceManager.h"
#include "Texture.h"
class TextureManager : public ResourceManager
{
public:
	TextureManager();
	virtual~TextureManager();
	bool Release();
public:
	TexturePtr CreateTuextureFromeFile(const wchar_t* file_path);
	TexturePtr CreateTuexture(const TMath::Rect& size, Texture::Type type);
protected:
	virtual Resource* CreateResourceFromFileConcre(const wchar_t* file_path);

};

