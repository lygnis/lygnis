#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager(): ResourceManager()
{

}
TextureManager::~TextureManager()
{
    ResourceManager::Release();
}

TexturePtr TextureManager::CreateTuextureFromeFile(const wchar_t* file_path)
{
    return std::static_pointer_cast<Texture>(CreateResourceFromFile(file_path));
}

TexturePtr TextureManager::CreateTuexture(const TMath::Rect& size, Texture::Type type)
{
    Texture* tex = nullptr;
    try
    {
        tex = new Texture(size, type);
    }
    catch (...)
    {

    }
    TexturePtr res(tex);
    return res;
}

Resource* TextureManager::CreateResourceFromFileConcre(const wchar_t* file_path)
{
    Texture* tex = nullptr;
    try
    {
        tex = new Texture(file_path);
    }
    catch (...)
    {

    }
    return tex;
}
bool TextureManager::Release()
{
    return true;
}
