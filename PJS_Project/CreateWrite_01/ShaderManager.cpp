#include "ShaderManager.h"

void ShaderManager::SetDevice(ID3D11Device* _p3dDevice, ID3D11DeviceContext* _pImmediateContext)
{
	m_p3dDevice = _p3dDevice;
	m_pImmediateContext = _pImmediateContext;
}

Shader* ShaderManager::LoadShader(std::wstring _shName)
{
	HRESULT hr;
	// �ߺ�����
	// ���̴��� ���� �� �� �ߺ��Ǵ°��� ������ �� ���̴��� ��ȯ�Ѵ�.
	auto iter = m_ShaderList.find(_shName);
	if (iter != m_ShaderList.end())
	{
		return iter->second;
	}
	Shader* newShader = new Shader;
	if (newShader)
	{
		hr = newShader->LoadShader(m_p3dDevice, m_pImmediateContext, _shName);
		if (SUCCEEDED(hr))
		{
			m_ShaderList.insert(std::make_pair(_shName, newShader));
		}
	}
	return newShader;
}

bool ShaderManager::Release()
{
	for (auto data : m_ShaderList)
	{
		Shader* shader = data.second;
		if (shader)
			shader->Release();
		delete shader;
	}
	m_ShaderList.clear();
	return true;
}
