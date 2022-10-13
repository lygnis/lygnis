#pragma once
#include "TDevice.h"
#include "TInput.h"
#include "TTimer.h"
#include "TWriter.h"
#include "TDxState.h"
#include "TSoundManager.h"
#include "TTextureManager.h"
#include "TShaderManager.h"
//#include "TSpriteManager.h"
class TGameCore : public TDevice
{
public:
	TWriter				m_Writer;
	bool m_bGameRun = true;
public:
	virtual bool		Init() {return true;}; // 초기화
	virtual bool		Frame() { return true; }; // 실시간 계산
	virtual bool		Render() { return true; }; // 실시간 랜더링
	virtual bool		Release() { return true; }; // 소멸 및 삭제
private:
	bool		TCoreInit(); // 초기화
	bool		TCoreFrame();// 실시간 계산
	bool		TCorePreRender();
	bool		TCoreRender();// 실시간 랜더링
	bool		TCorePostRender();
	bool		TCoreRelease();// 소멸 및 삭제	
public:
	bool		Run() override;
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();
};

