#include "MVertexShader.h"
#include "MGraphicsEngine.h"

bool MVertexShader::Init(void* shader_byte_code, size_t byte_code_size)
{
    HRESULT hr;

    hr = MGraphicsEngine::get()->_d3d_Device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, _vs.GetAddressOf());
    if (FAILED(hr))
    {
        assert(false);
        return false;
    }

    return true;
}
