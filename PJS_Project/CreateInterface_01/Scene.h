#pragma once
#include "Player.h"
#include "TStd.h"
#include "Writer.h"
class Scene
{
public:
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	IDXGISwapChain*			m_pSwapChain;
public:
	// Player*		m_pPlayer;
	Rect		m_rtMap;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	bool SetDevice(ID3D11Device* _pd3dDevice, ID3D11DeviceContext* _pImmediateContext);
	bool GetSwapChain(IDXGISwapChain* _pSwapChain);
};

