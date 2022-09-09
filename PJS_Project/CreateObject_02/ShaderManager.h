#pragma once
#include "Shader.h"
class ShaderManager : public SingleTone<ShaderManager>
{
public:
	ID3D11Device* m_p3dDevice = nullptr;		// 1번 디바이스 획득 (디바이스 객체)
	ID3D11DeviceContext* m_pImmediateContext = nullptr;		// 즉시
	void SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext);
public:
	std::map<std::wstring, Shader*> m_ShaderList;			// 쉐이더 리스트 생성

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

