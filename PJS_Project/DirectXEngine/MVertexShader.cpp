#include "MVertexShader.h"
#include "RenderSystem.h"
#include <exception>

MVertexShader::MVertexShader(const wchar_t* full_path, const char* entry_point ,RenderSystem* system) : _system(system)
{
	HRESULT hr;
	ComPtr<ID3DBlob> blob;
	ComPtr<ID3DBlob> errCode;


	hr = D3DCompileFromFile(full_path, nullptr, nullptr,
        entry_point, "vs_5_0", 0, 0, &blob, &errCode);
    if (FAILED(hr))
    {
		if (errCode != NULL)
		{
			OutputDebugStringA((char*)errCode->GetBufferPointer());
		}
        assert(false);
    }
    hr = _system->_d3d_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, _vsShader.GetAddressOf());
	if (FAILED(hr))
	{
		assert(false);
	}

}
