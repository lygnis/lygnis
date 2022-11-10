#pragma once
#include "Texture.h"
class TextureManager : public SingleTone<TextureManager>
{
public:
	ID3D11Device* m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)		// �Ҹ��Ҷ� ������ ���� ���� ������ Nullptr�� ����
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// ���
public:
	std::map<std::wstring, Texture*> m_TextureList;
public:
	void SetDvice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
	Texture* LoadTexture(std::wstring _fileName);
	Texture* FindTexture(std::wstring _fileName);
	bool Release();
private:
	friend class SingleTone<TextureManager>;
public:
	TextureManager() {};
	~TextureManager() {};
};
#define I_Tex TextureManager::GetInstance()
