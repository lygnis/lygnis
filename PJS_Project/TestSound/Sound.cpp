#include "Sound.h"

bool Sound::Load(FMOD::System* _pSystem, std::wstring _fileName)
{
	// 사운드 받아오기
	m_pSystem = _pSystem;
	FMOD_RESULT fr = m_pSystem->createSound(to_wm(_fileName).c_str(), FMOD_DEFAULT, nullptr, &m_pSound);
	if (fr == FMOD_OK)
	{
		//m_pSound->getLength()
		return true;
	}
	return false;
}


bool Sound::Play(bool bLoop)
{
	// 사운드 실행하기
	if (IsPlay() == false)
	{
		FMOD_RESULT fr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (fr == FMOD_OK)
		{
			m_fVolume = 0.5f;
			SetLoop(bLoop);
			m_pChannel->setVolume(m_fVolume);
		}
	}
	return true;
}

bool Sound::IsPlay()
{
	// 사운드가 실행중이면 true로 바꿔 소리가 중복이 안되도록 한다.
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	return playing;
}

void Sound::Paused()
{
	// 사운드 일시정지 시키기
	if (m_pChannel == nullptr)
		return;
	bool paused;
	m_pChannel->getPaused(&paused);
	m_pChannel->setPaused(!paused);
}

void Sound::Stop()
{
	m_pChannel->stop();
}

void Sound::SetLoop(bool bLoop)
{
	if (bLoop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);
}

void Sound::VolumeUp(float _volume)
{
	m_fVolume += _volume;
	m_fVolume = min(1.0f, m_fVolume);
	m_pChannel->setVolume(m_fVolume);
}

void Sound::VolumeDown(float _volume)
{
	m_fVolume += _volume;
	m_fVolume = max(1.0f, m_fVolume);
	m_pChannel->setVolume(m_fVolume);
}

bool Sound::Init()
{
	// 1. systemCreate함수를 생성
	FMOD::System_Create(&m_pSystem);
	// 생성한 시스템 초기화하기 32개의 사운드를 받을 수 있다.
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);

	return true;
}

bool Sound::Frame()
{
	return true;
}

bool Sound::Render()
{
	return true;
}

bool Sound::Release()
{
	if (m_pSound)m_pSound->release();
	//if (m_pSystem)m_pSystem->close();
	//if (m_pSystem)m_pSystem->release();
	return true;
}
