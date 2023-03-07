#include "Texture.h"
#include "MGraphicsEngine.h"
#include "ResourceManager.h"
#include "Game.h"
#include "RenderSystem.h"
Texture::Texture(const wchar_t* full_path, ResourceManager* manager) : Resource(full_path, manager)
{
	texture_ = manager->GetGame()->GetGraphicsEngine()->getRenderSystem()->CreateTexture(full_path);
}
