#include "Sound.h"

bool Sound::Load(FMOD::System* _pSystem, std::wstring _fileName)
{
	// ���� �޾ƿ���
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
	// ���� �����ϱ�
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
	// ���尡 �������̸� true�� �ٲ� �Ҹ��� �ߺ��� �ȵǵ��� �Ѵ�.
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	return playing;
}

void Sound::Paused()
{
	// ���� �Ͻ����� ��Ű��
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
	// 1. systemCreate�Լ��� ����
	FMOD::System_Create(&m_pSystem);
	// ������ �ý��� �ʱ�ȭ�ϱ� 32���� ���带 ���� �� �ִ�.
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
