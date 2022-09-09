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
    // �������̾ƿ��� ������� �������̴� �ݵ�� �������� �ʿ��ϴ�.

    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(_sFileName.c_str(), NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVSCode, &pErrorCode);            // ���̴����� �̸�, Nll, Null,�Լ��̸�, ���ؽ� ���̴� �����Ϸ�vs_5_0
    // Blob���� ��ȯ�ȴ�. pVSCode,  ������ ����� pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    // ���̴� ����
    m_p3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    //�ȼ� ���̴� ������

    hr = D3DCompileFromFile(_sFileName.c_str(), NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCode, &pErrorCode);    // ���̴����� �̸�, Nll, Null,�Լ��̸�, ���ؽ� ���̴� �����Ϸ�vs_5_0
    // Blob���� ��ȯ�ȴ�. pVSCode,  ������ ����� pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }
    // ���̴� ����
    m_p3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);
    if (FAILED(hr))
    {
        OutputDebugStringA((char*)pErrorCode->GetBufferPointer());      // �ݵ�� �����ڵ� ����
        pErrorCode->Release();
        return hr;
    }
    return hr;
}
