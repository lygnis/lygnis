#include "Button.h"
#include "MGraphicsEngine.h"
#include <exception>
#include "Texture.h"
Button::Button(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path) : Sprite(vertex_shader_path,  pixel_shader_path)
{
	
}
Button::Button(const ButtonPtr& button) : Sprite(button)
{

}