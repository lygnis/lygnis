#pragma once
#include "Sprite.h"
class SpriteManager : public SingleTone<SpriteManager>
{
public:
	//std::vector<W_STR> m_rtNameList;						// ����Ʈ ��������Ʈ �̸�
	//std::vector<RECT_ARRAY> m_rtSpriteList;					// ����Ʈ ��������Ʈ ��ǥ ��
public:
	ID3D11Device* m_p3dDeivce;
	ID3D11DeviceContext* m_pImmendiateContext;
private:
	friend class SingleTone<SpriteManager>;
	std::map<std::wstring, Sprite*>m_List;					// ����Ʈ ��������Ʈ �̹���
	std::map<W_STR, std::vector<W_STR>>	m_rtNameList;							// �ؽ�Ʈ ���� ����Ʈ
	std::map<W_STR, std::vector<RECT_ARRAY>> m_rtSpriteList;
public:
	bool		GameDataLoad(const TCHAR* _fileName);
	bool		Load(const WCHAR* _txtName, const WCHAR* _fileName);
	bool		SetDevice(ID3D11Device* _p3dDeivce, ID3D11DeviceContext* _pImmendiateContext);
	Sprite*		Find(std::wstring name);

	bool		Release();
	Sprite*		GetPtr(W_STR name);
	Sprite&		Get(W_STR name);
private:
	SpriteManager()
	{};
public:
	~SpriteManager();
};

#define I_Sprite SpriteManager::GetInstance()
