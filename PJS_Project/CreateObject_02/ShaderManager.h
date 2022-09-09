#pragma once
#include "Shader.h"
class ShaderManager : public SingleTone<ShaderManager>
{
public:
	ID3D11Device* m_p3dDevice = nullptr;		// 1�� ����̽� ȹ�� (����̽� ��ü)
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// ���
	void SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
public:
	std::map<std::wstring, Shader*> m_ShaderList;			// ���̴� ����Ʈ ����

public:
	Shader* LoadShader(std::wstring _shName);
	bool Release();

private:
	ShaderManager() {};
public:
	~ShaderManager()
	{
		Release();
	}
};

