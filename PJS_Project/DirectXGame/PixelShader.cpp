#include "PixelShader.h"
#include "MGraphicsEngine.h"

bool PixelShader::Init(const void* shader_byte_code, size_t byte_code_size)
{
    HRESULT hr;

    hr = MGraphicsEngine::get()->_d3d_Device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, _psShader.GetAddressOf());
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    return true;
}
