#include "SpriteManager.h"
bool SpriteManager::GameDataLoad(const TCHAR* _fileName)
{
    TCHAR pBuffer[256] = { 0 };
    TCHAR pTemp[256] = { 0 };
    std::ifstream read;
    read.open("Spriteinfo.prn", std::ios_base::in);
    float nums[5];
    float maxCount = 0;
    read >> maxCount;
    m_rtSpriteList.resize(maxCount);
    std::string trash;
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
            continue;
        }
        if (read.eof())
        {
            break;
        }

        Rect rt;
        rt = { nums[1], nums[2], nums[3], nums[4] };
        m_rtSpriteList[nums[0]].push_back(rt);
    }
    read.close();
    return true;
}

bool SpriteManager::Load(std::wstring _name)
{
    m_rtSpriteList.clear();
    m_rtNameList.clear();
    if (GameDataLoad(_name.c_str()) == false)
    {
        return false;                           // ���� �����͸� �ε����� ���ϸ� 
    }
    fileList.push_back(_name);

    HRESULT hr;
    for (int iSp = 0; iSp < m_rtSpriteList.size(); iSp++)
    {
        // �ߺ�����
        auto data = Find(m_rtNameList[iSp]);
        if (data != nullptr)
            continue;               // ��������Ʈ ����Ʈ���� �̸��� ã�´� ���� �̸��� ������ ������ continue;
        Sprite* pNewData = new Sprite;
        pNewData->m_szName = m_rtNameList[iSp];             // ���ο� ��������Ʈ�� �����Ѵ�. ���ο� ��������Ʈ �̸��� ���� �̸�����Ʈ
        if (pNewData)
        {
            hr = pNewData->Load(m_p3dDeivce, m_pImmendiateContext, _name);
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
    return true;
}

Sprite* SpriteManager::GetPtr(W_STR name)
{
    return nullptr;
}

Sprite& SpriteManager::Get(W_STR name)
{
    // TODO: ���⿡ return ���� �����մϴ�.
}

SpriteManager::~SpriteManager()
{
    Release();
}
