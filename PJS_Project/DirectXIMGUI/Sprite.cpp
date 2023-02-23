#include "Sprite.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"

Sprite::Sprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path) : ControlUI(vertex_shader_path, pixel_shader_path)
{

}


Sprite::~Sprite()
{
}

