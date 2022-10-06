#pragma once
#include"TStd.h"
#include"fmod.h"
#include"fmod.hpp"
#include"fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")

class Sound
{
public:
	std::wstring	m_szName;
	FMOD::System*	m_pSystem = nullptr;
	FMOD::Sound*	m_pSound = nullptr;
	FMOD::Channel*	m_pChannel = nullptr;
	float			m_fVolume;
public:
	bool Load (FMOD::System*_pSystem, std::wstring _fileName);						// 사운드 불러오기
	bool Play(bool bLoop =false);							// 사운드 실행하기
	bool IsPlay();
	void Paused();
	void Stop();
	void SetLoop(bool bLoop = false);
	void VolumeUp(float _volume);
	void VolumeDown(float _volume);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

