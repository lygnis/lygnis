#pragma once
#include "Sprite.h"
class SpriteManager : public SingleTone<SpriteManager>
{
public:
	std::vector<W_STR> m_rtNameList;						// 이펙트 스프라이트 이름
	std::vector<RECT_ARRAY> m_rtSpriteList;					// 이펙트 스프라이트 좌표 값
public:
	ID3D11Device* m_p3dDeivce;
	ID3D11DeviceContext* m_pImmendiateContext;
private:
	friend class SingleTone<SpriteManager>;
	std::map<std::wstring, Sprite*>m_List;					// 이펙트 스프라이트 이미지
	std::vector<W_STR>	fileList;							// 텍스트 파일 리스트
public:
	bool		GameDataLoad(const TCHAR* _fileName);
	bool		Load(const WCHAR* _txtName);
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
