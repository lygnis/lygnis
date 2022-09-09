#pragma once
#include "TWindow.h"
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#include <d3d11.h>
#include "DxDevice.h"
#include "BaseObject.h"
#include "GameCore.h"

class Sample : public GameCore
{
public:
	//DxDevice m_dxDevice;			// ����� ���ؼ��� �����ϴ�
	GameCore	m_gEngine;
	//BaseObject	m_bObject;

public:
	bool		Init(); // �ʱ�ȭ
	bool		Frame();// �ǽð� ���
	bool		Render();// �ǽð� ������
	bool		Release();// �Ҹ� �� ����
public:
	Sample() {};
	~Sample() {};
};

