#include "Sample.h"
HRESULT Sample::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC ���� ������ǥ��
    // x-> -1 ~ +1
    // y-> -1 ~ +1
    // z-> 0 ~+1
    SimpleVertex vertices[] =
    {
        -0.5f, 0.5f, 0.0,  1.0f, 0.0f, 0.0f,0.5f,       // v0
         0.5f, 0.5f, 0.0,  0.0f, 1.0f, 0.0f,0.5f,       // v1
        -0.5f, -0.5f, 0.0, 0.0f, 0.0f, 1.0f,0.5f         // v2
    };
    D3D11_BUFFER_DESC        bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex)*3;        // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT;               // ������ �Ҵ� ��ҳ����� ���ۿ뵵 ��а��� ����Ʈ
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;      // �� ���۰� ������� gpu������ ����Ʈ �뷮�� ���۸� �Ҵ����ش�.
    //bd.CPUAccessFlags = 0;                          // cpu�� GPU�� ������ �� ����.
    //bd.MiscFlags = 0;                           // �⵿���
    //bd.StructureByteStride = 0;
    //CPU�� �������� ���� ������ ����.

    D3D11_SUBRESOURCE_DATA   sd;
    sd.pSysMem = vertices;              // �ý��� �޸� ���� ������ �ּҸ� �Ѱ��ش�.
    sd.SysMemPitch = 0;                 // 2���� 3���� ���� ���
    sd.SysMemSlicePitch =0;
    hr = m_p3dDevice->CreateBuffer(&bd,  &sd,&m_pVertexBuffer);          // ���۸� ����
    // bd = ���� �Ҵ�
    // sd = �ʱ� �Ҵ�� ���۸� ü��� CPU�޸� �ּ� sd�� ���̸� �޸𸮸� ���� ���߿� GPU�޸𸮸� ä���� �Ѵ�.
    // �Ҵ�� VertexBuffer�� ���� CPU�� ���� ���Ѵ�.
    return hr;
}
HRESULT Sample::CreateShader()
{
    HRESULT hr;
    // �������̾ƿ��� ������� �������̴� �ݵ�� �������� �ʿ��ϴ�.

    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "VS", "vs_5_0", 0, 0, &m_pVSCode, &pErrorCode);            // ���̴����� �̸�, Nll, Null,�Լ��̸�, ���ؽ� ���̴� �����Ϸ�vs_5_0
    // Blob���� ��ȯ�ȴ�. pVSCode,  ������ ����� pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return false;
    }
    // ���̴� ����
    m_p3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);

    //�ȼ� ���̴� ������

    hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &m_pPSCode, &pErrorCode);    // ���̴����� �̸�, Nll, Null,�Լ��̸�, ���ؽ� ���̴� �����Ϸ�vs_5_0
    // Blob���� ��ȯ�ȴ�. pVSCode,  ������ ����� pErrorCode 
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return false;
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
        return false;
    }
}
HRESULT Sample::CreateVertexLayout()
{
    HRESULT hr;

    // �������̾ƿ��� �������̴��� ������ ������ �ִ�.
    // �� ���ؽ� ���ۿ��ִ� ������ ���� �ֳ�?
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },       // ��ġ Float 3��
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }           // ���� ������ ������ Float 4��
    };
    // ���� ���̾ƿ� ������ ������ �������̴� ������ �ʿ��ϴ�.
    // ���̴��� �ѱ涧 ���̴����� ��ȯ�ϴ°ͺ��� �� ������ �ȵȴ�. ¦�� �¾ƾ��Ѵ�.
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    // float 0~7
    // pos 0~3, 0~11
    // color 4~7 12~28
    // �� ���ؽ��� �÷Լ� �� ����Ʈ ��

    /*ied.SemanticName = "POSITION";
    ied.SemanticIndex = 0;
    ied.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    ied.InputSlot = 0;
    ied.AlignedByteOffset = 0;
    ied.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    ied.InstanceDataStepRate = 0;*/

    hr = m_p3dDevice->CreateInputLayout(
        ied, NumElements, 
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
    return hr;
}

bool		Sample::Init()
{
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader()))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    return true;
}
bool		Sample::Frame()
{
    return true;
}
bool		Sample::Render()
{
    UINT stride = sizeof(SimpleVertex);         // �����Ѱ��� ����Ʈ �뷮
    UINT offset = 0;                            // �������ۿ��� �������(����Ʈ)
    // �ﰢ�� ������
    // Get�� ���� ������� �ʴ´�.
    // ���ؽ� ������ �� 1, 0��° ��������(�������͸�)
    // ������ ������ ��� ó���Ǵ��� ����
    m_pImmediateContext->IASetVertexBuffers(0,1,& m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    m_pImmediateContext->HSSetShader(NULL, NULL, 0);        // ������ �ʿ�� ����
    m_pImmediateContext->DSSetShader(NULL, NULL, 0);
    m_pImmediateContext->GSSetShader(NULL, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);      // �Ƚ����̴��� �ʼ�

    // ��ο� ����� �������� ���������ο� ���� �����ȴ�.
    // �� ������ �߿����� �ʴ�.
    //m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);             //fkdlsfltmxm
    m_pImmediateContext->Draw(3, 0);
    return true;
}
bool		Sample::Release()
{   
    if (m_pVertexBuffer)
       m_pVertexBuffer->Release();
    if (m_pVertexLayout)
        m_pVertexLayout->Release();
    if (m_pVS)
        m_pVS->Release();
    if (m_pPS)
        m_pPS->Release();
    if (m_pVSCode)
        m_pVSCode->Release();
    if (m_pPSCode)
        m_pPSCode->Release();

     return true;

}



GAME_RUN(P2_CreateDevice_01, 1024, 768)
