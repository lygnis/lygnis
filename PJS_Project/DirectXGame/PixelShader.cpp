#include "PixelShader.h"
#include "RenderSystem.h"
#include <exception>

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size ,RenderSystem* system): _system(system)
{
    HRESULT hr;

    hr = _system->_d3d_Device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, _psShader.GetAddressOf());
    if (FAILED(hr))
    {
        assert(false);
        throw std::exception("PixelShader not create successfully");
    }
}

