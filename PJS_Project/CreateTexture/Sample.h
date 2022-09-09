#pragma once
#include "TWindow.h"
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#include <d3d11.h>
#include "DxDevice.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#pragma comment(lib, "DirectXTK.lib")
//#pragma comment(lib, "DirectXTK.lib")
class Sample : public DxDevice
{
public:
	//DxDevice m_dxDevice;			// ����� ���ؼ��� �����ϴ�
	ID3D11ShaderResourceView*	m_pShaderResourceView = nullptr;
	ID3D11Resource*				m_pResource = nullptr;			// �������� �̹��� ����
public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����

};

