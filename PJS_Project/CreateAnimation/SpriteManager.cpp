#include "SpriteManager.h"
#include "Player.h"
bool SpriteManager::GameDataLoad(const TCHAR* _fileName)
{
    TCHAR pBuffer[256] = { 0 };
    TCHAR pTemp[256] = { 0 };
    std::ifstream read;
    read.open( _fileName, std::ios_base::in);
    float nums[5];
    float maxCount = 0;
    read >> maxCount;
    m_rtSpriteList.resize(maxCount);
    std::string trash;
    int iIndex = -1;
    while (true)
    {
        read >> nums[0];
        read >> nums[1];
        read >> nums[2];
        read >> nums[3];
        read >> nums[4];
        if (read.fail())
        {
            read.clear();
            read >> trash;
            if (trash == "END")
                break;
            else
            {
                m_rtNameList.push_back(to_mw(trash));
                iIndex++;
            }
            continue;
        }
        if (read.eof())
        {
            break;
        }

        Rect rt;
        rt = { nums[1], nums[2], nums[3], nums[4] };
        m_rtSpriteList[iIndex].push_back(rt);
    }
    read.close();
    return true;
}

bool SpriteManager::Load(const WCHAR* _txtName)
{
    m_rtSpriteList.clear();
    m_rtNameList.clear();
    if (GameDataLoad(_txtName) == false)
    {
        return false;                           // ���� �����͸� �ε����� ���ϸ� 
    }
    fileList.push_back(_txtName);

    HRESULT hr;
    for (int iSp = 0; iSp < m_rtSpriteList.size(); iSp++)
    {
        // �ߺ�����
        auto data = Find(m_rtNameList[iSp]);
        if (data != nullptr)
            continue;                                       // ��������Ʈ ����Ʈ���� �̸��� ã�´� ���� �̸��� ������ ������ continue;
        Sprite* pNewData = new Sprite;
        pNewData->m_szName = m_rtNameList[iSp];             // ���ο� ��������Ʈ�� �����Ѵ�. ���ο� ��������Ʈ �̸��� ���� �̸�����Ʈ
        pNewData->m_uvArray = m_rtSpriteList[iSp];
        if (pNewData)
        {
            hr = pNewData->SetDevice(m_p3dDeivce, m_pImmendiateContext);
            hr = pNewData->Load(_txtName);
            if (SUCCEEDED(hr))
            {
                m_List.insert(std::make_pair(pNewData->m_szName, pNewData));
            }
        }
    }
    return true;
}

bool SpriteManager::SetDevice(ID3D11Device* _p3dDeivce, ID3D11DeviceContext* _pImmendiateContext)
{
    m_p3dDeivce = _p3dDeivce;
    m_pImmendiateContext = _pImmendiateContext;
    return true;
}

Sprite* SpriteManager::Find(std::wstring name)
{
    auto iter = m_List.find(name);
    if (iter != m_List.end())
    {
        Sprite* pData = iter->second;
        return pData;
    }
    return nullptr;
}

bool SpriteManager::Release()
{
    for (auto data : m_List)
    {
        Sprite* pData = data.second;
        if (pData)pData->Release();
        delete pData;
    }
    fileList.clear();
    m_rtSpriteList.clear();
    m_rtNameList.clear();
    m_List.clear();
    return true;
}

Sprite* SpriteManager::GetPtr(W_STR name)
{
    auto iter = m_List.find(name);
    if (iter != m_List.end())
    {
        Sprite* pData = iter->second;
        return pData;
    }
    return nullptr;
}

Sprite& SpriteManager::Get(W_STR name)
{
    auto iter = m_List.find(name);
    if (iter != m_List.end())
    {
        Sprite* pData = iter->second;
        return *pData;
    }
    // TODO: ���⿡ return ���� �����մϴ�.
}

SpriteManager::~SpriteManager()
{
    Release();
}
