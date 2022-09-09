#include "Timer.h"
bool Timer::Init()
{
	m_fGameTime = 0;
	m_fBeforTime = timeGetTime();
	m_fFpsTime = 0.1f;
	return true;
}
bool Timer::Frame()
{
	m_fElapseTime = timeGetTime();
	DWORD currTime = m_fElapseTime - m_fBeforTime;
	m_fDeltaTime = currTime / 1000.0f;
	m_fGameTime += m_fDeltaTime;
	m_fFpsTime += m_fDeltaTime;
	m_iFPScount++;
	if (m_fFpsTime >= 1.0f)
	{
		m_iFPS = m_iFPScount;
		m_iFPScount = 0;
		m_fFpsTime -= 1.0f;
	}
	m_fBeforTime = m_fElapseTime;

	return true;
}
bool Timer::Render()
{
	m_szTimeNFps = std::to_wstring(m_fGameTime);
	m_szTimeNFps +=  L" ";
	m_szTimeNFps += std::to_wstring(m_iFPS);
	m_szTimeNFps += '\n';
	OutputDebugString(m_szTimeNFps.c_str());
	return true;
}
bool Timer::Release()
{
	return true;
}