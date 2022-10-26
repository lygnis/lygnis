#pragma once
#include "TStd.h"
class MTimer : public SingleTone<MTimer>
{
private:
	LARGE_INTEGER	m_Frequency;		// �ʴ� ���ļ�
	LARGE_INTEGER	m_Start;			// �̺�Ʈ Ÿ�̸� ���� �ð�
	LARGE_INTEGER	m_Elapse;			// �̺�Ʈ Ÿ�̸� ��� �ð�
	LARGE_INTEGER	m_FPS;				// FPS üũ Ÿ�̸�
	int				m_iFramePerSecond;	// ������ ��� �ð�
	int				m_iFPSElapse;		// �ʴ� ����� ������
	bool			m_bStarted;			// �̺�Ʈ Ÿ�̸� �۵� ����

public:
	LARGE_INTEGER	m_Current;			// ����ð�
	LARGE_INTEGER	m_Frame;			// ���� �������� �ð� üũ
	float			m_fDeltaTime;		// ������ ��� �ð�
	float			m_fEventTime;		// �̺�Ʈ Ÿ�̸�
	std::wstring	m_szTimeNFps;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void Reset();
	void Start();
	void Stop();
	bool IsStarted() const;
public:
	MTimer();
	~MTimer();
};

#define I_Timer MTimer::GetInstance()

