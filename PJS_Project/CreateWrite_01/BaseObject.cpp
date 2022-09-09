#include "BaseObject.h"


bool BaseObject::SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext)
{
    m_p3dDevice = _p3dDevice;
    m_pImmediateContext = _pImmediateContext;
    m_shManger.SetDevice(m_p3dDevice, m_pImmediateContext);
    m_txManager.SetDvice(m_p3dDevice, m_pImmediateContext);
    if (m_p3dDevice == nullptr || m_pImmediateContext == nullptr)
        return false;
    return true;
}
HRESULT BaseObject::CreateVertexBuffer()
{
    HRESULT hr;
    // NDC ���� ������ǥ��
    // x-> -1 ~ +1
    // y-> -1 ~ +1
    // z-> 0 ~+1
    m_pVertexList.resize(6);
    m_pVertexList[0].p = { -1.0f, 1.0f, 0.0f };
    m_pVertexList[1].p = { 1.0f, 1.0f, 0.0f };
    m_pVertexList[2].p = { -1.0f, -1.0f, 0.0f };
    m_pVertexList[3].p = { -1.0f, -1.0f, 0.0f };
    m_pVertexList[4].p = { 1.0f, 1.0f, 0.0f };
    m_pVertexList[5].p = { 1.0f, -1.0f, 0.0f };

    m_pVertexList[0].c = { -1.0f, 1.0f, 0.0f, 1.0f };
    m_pVertexList[1].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[2].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[3].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[4].c = { -1.0f, 1.0f, 0.0f , 1.0f };
    m_pVertexList[5].c = { -1.0f, 1.0f, 0.0f, 1.0f };

    m_pVertexList[0].t = { 0.0f, 0.0f };
    m_pVertexList[1].t = { 1.0f, 0.0f };
    m_pVertexList[2].t = { 0.0f, 1.0f };
    m_pVertexList[3].t = { 0.0f, 1.0f };
    m_pVertexList[4].t = { 1.0f, 0.0f };
    m_pVertexList[5].t = { 1.0f, 1.0f };
    UINT NumVertex = m_pVertexList.size();

    D3D11_BUFFER_DESC        bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex)*NumVertex;                    // ����Ʈ �뷮
    // GPU �޸𸮿� �Ҵ�
    bd.Usage = D3D11_USAGE_DEFAULT;                             // ������ �Ҵ� ��ҳ����� ���ۿ뵵 ��а��� ����Ʈ
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;                    // �� ���۰� ������� gpu������ ����Ʈ �뷮�� ���۸� �Ҵ����ش�.
    //bd.CPUAccessFlags = 0;                                    // cpu�� GPU�� ������ �� ����.
    //bd.MiscFlags = 0;                                         // �⵿���
    //bd.StructureByteStride = 0;
    //CPU�� �������� ���� ������ ����.

    D3D11_SUBRESOURCE_DATA   sd;
    sd.pSysMem = &m_pVertexList.at(0);                          // �ý��� �޸� ���� ������ �ּҸ� �Ѱ��ش�.
    sd.SysMemPitch = 0;                                         // 2���� 3���� ���� ���
    sd.SysMemSlicePitch = 0;
    hr = m_p3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);          // ���۸� ����
    // bd = ���� �Ҵ�
    // sd = �ʱ� �Ҵ�� ���۸� ü��� CPU�޸� �ּ� sd�� ���̸� �޸𸮸� ���� ���߿� GPU�޸𸮸� ä���� �Ѵ�.
    // �Ҵ�� VertexBuffer�� ���� CPU�� ���� ���Ѵ�.
    return hr;
}
HRESULT BaseObject::CreateShader(std::wstring _shName)
{
    m_pShader = m_shManger.LoadShader(_shName);
    if (m_pShader)
        return true;
    return false;
}
HRESULT BaseObject::LoadTexture(std::wstring _fileName)
{
    
    m_pTexture = m_txManager.LoadTexture(_fileName);
    if (m_pTexture)
        return true;
    return false;
}
bool BaseObject::Create(ID3D11Device* p3dDevice, ID3D11DeviceContext* _pImmediateContext, const wchar_t* _texName, const wchar_t* _shName)
{
    if ((SetDevice(p3dDevice, _pImmediateContext)) == false)
    {
        return false;
    }
    if (FAILED(CreateVertexBuffer()))
    {
        return false;
    }
    if (FAILED(CreateShader(_shName)))
    {
        return false;
    }
    if (FAILED(CreateVertexLayout()))
    {
        return false;
    }
    if (FAILED(LoadTexture(_texName)))
    {
        return false;
    }
    return true;
}
bool BaseObject::Init()
{
    return true;
}
bool BaseObject::Frame()
{
    return true;
}
bool BaseObject::Render()
{
    UINT stride = sizeof(SimpleVertex);         // �����Ѱ��� ����Ʈ �뷮
    UINT offset = 0;                            // �������ۿ��� �������(����Ʈ)
    // �ﰢ�� ������
    // Get�� ���� ������� �ʴ´�.
    // ���ؽ� ������ �� 1, 0��° ��������(�������͸�)
    // ������ ������ ��� ó���Ǵ��� ����
    m_pImmediateContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    m_pImmediateContext->VSSetShader(m_pShader->m_pVS, NULL, 0);
    m_pImmediateContext->HSSetShader(NULL, NULL, 0);        // ������ �ʿ�� ����
    m_pImmediateContext->DSSetShader(NULL, NULL, 0);
    m_pImmediateContext->GSSetShader(NULL, NULL, 0);
    m_pImmediateContext->PSSetShader(m_pShader->m_pPS, NULL, 0);      // �Ƚ����̴��� �ʼ�

    // ��ο� ����� �������� ���������ο� ���� �����ȴ�.
    // �� ������ �߿����� �ʴ�.
    //m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);    
    m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture->m_pSrvTexture);
    m_pImmediateContext->Draw(m_pVertexList.size(), 0);
    return true;
}
bool BaseObject::Release()
{
    if (m_pVertexBuffer)
        m_pVertexBuffer->Release();
    if (m_pVertexLayout)
        m_pVertexLayout->Release();
    if(m_pShader)m_pShader->Release();

    return true;
}
HRESULT BaseObject::CreateVertexLayout()
{
    HRESULT hr;

    // �������̾ƿ��� �������̴��� ������ ������ �ִ�.
    // �� ���ؽ� ���ۿ��ִ� ������ ���� �ֳ�?
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },       // ��ġ Float 3��
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },           // ���� ������ ������ Float 4��
        {"Texture", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
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
        m_pShader->m_pVSCode->GetBufferPointer(),
        m_pShader->m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);
    return hr;
}