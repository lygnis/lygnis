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
