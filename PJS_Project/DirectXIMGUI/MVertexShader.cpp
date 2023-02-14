#include "MVertexShader.h"
#include "RenderSystem.h"
#include <exception>

MVertexShader::MVertexShader(const void* shader_byte_code, size_t byte_code_size ,RenderSystem* system) : _system(system)
{
    HRESULT hr;

    hr = _system->_d3d_Device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, _vsShader.GetAddressOf());
    if (FAILED(hr))
    {
        assert(false);
        throw std::exception("VertexShader not create successfully");
    }
}
