#include "Shader.h"

bool Shader::Init()
{
    return false;
}

bool Shader::Frame()
{
    return false;
}

bool Shader::Render()
{
    return false;
}

bool Shader::Release()
{
    if (m_pVS)
        m_pVS->Release();
    if (m_pPS)
        m_pPS->Release();
    if (m_pVSCode)
        m_pVSCode->Release();
    if (m_pPSCode)
        m_pPSCode->Release();
     m_pVS = nullptr;
     m_pPS = nullptr;
     m_pVSCode = nullptr;
     m_pPSCode = nullptr;

     return true;
}

HRESULT Shader::LoadShader(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext, std::wstring _sFileName)
{
    m_p3dDevice = _p3dDevice;
    m_pImmediateContext = _pImmediateContext;
    HRESULT hr;
    // 정점레이아웃을 만들려면 정점쉐이더 반드시 컴파일이 필요하다.

    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(_sFileName.c_str(), NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVSCode, &pErrorCode);            // 쉐이더파일 이름, Nll, Null,함수이름, 버텍스 쉐이더 컴파일러vs_5_0
    // Blob으로 반환된다. pVSCode,  오류가 생기면 pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    // 쉐이더 생성
    m_p3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    //픽셀 쉐이더 컴파일

    hr = D3DCompileFromFile(_sFileName.c_str(), NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCode, &pErrorCode);    // 쉐이더파일 이름, Nll, Null,함수이름, 버텍스 쉐이더 컴파일러vs_5_0
    // Blob으로 반환된다. pVSCode,  오류가 생기면 pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    // 쉐이더 생성
    m_p3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);
    if (FAILED(hr))
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());      // 반드시 에러코드 삽입
        pErrorCode->Release();
        return hr;
    }
    return hr;
}
