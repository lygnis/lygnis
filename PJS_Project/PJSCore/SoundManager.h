#pragma once
#include "Sound.h"
class SoundManager :public SingleTone<SoundManager>
{
	FMOD::System* m_pSystem = nullptr;
	std::list<std::wstring> m_fileList;
private:
	friend class SingleTone<SoundManager>;
	std::map<std::wstring, Sound*>m_List;
public:
	T_STR	GetSplitName(std::wstring _name);		//std::basic_string<TCHAR> T_STR
	void	LoadDir(std::wstring _path);
	void	LoadAll(std::wstring _name);
	bool	Init();
	bool	Frame();
	Sound*	Load(std::wstring _filename);
	bool	Release();
	Sound*	GetPtr(W_STR _name);					// std::basic_string<wchar_t> W_STR
private:
	SoundManager() {};
public:
	~SoundManager() { Release(); };
};

#define I_Sound SoundManager::GetInstance()

