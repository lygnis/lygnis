#include "SoundManager.h"
#include <io.h>
#include <tchar.h>
T_STR SoundManager::GetSplitName(std::wstring _name)
{
	W_STR name;
	TCHAR dirve[MAX_PATH] = {0,};
	TCHAR dir[MAX_PATH] = { 0, };
	TCHAR filename[MAX_PATH] = { 0, };
	TCHAR ext[MAX_PATH] = { 0, };
	_tsplitpath_s(_name.c_str(), dirve, dir, filename, ext);
	name = filename;
	name += ext;

	return name;
}
void SoundManager::LoadDir(std::wstring _path)
{
	W_STR dirpath = _path + L"*.*";			// 모든 파일이름 모든 확장명
	intptr_t handle;
	struct _wfinddata_t fd;
	handle = _wfindfirst(dirpath.c_str(), &fd);		// 경로에 있는 모든 파일을 읽는다.
	if (handle == -1L)
		return;
	do {
		// 디렉토리 라면
		if ((fd.attrib & _A_SUBDIR) && fd.name[0] != '.')
		{
			LoadDir(_path + fd.name + L"/");
		}
		else if (fd.name[0] != '.')
		{
			m_fileList.push_back(_path + fd.name);
		}
	} while (_wfindnext(handle, &fd) == 0);
	_findclose(handle);
}

void SoundManager::LoadAll(std::wstring _name)
{
	LoadDir(_name);
	for (auto& data : m_fileList)
	{
		Load(data);
	}
}

bool SoundManager::Init()
{
	// 시스템 초기화 하기
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	return true;
}

bool SoundManager::Frame()
{
	m_pSystem->update();
	for (auto data : m_List)
	{
		Sound* pData = data.second;
		if (pData) pData->Frame();
	}
	return true;
}

Sound* SoundManager::Load(std::wstring _filename)
{
	bool br;
	// m_szName = 파일이름+확장자
	W_STR name = GetSplitName(_filename);
	// 중복제거
	auto iter = m_List.find(name);
	if (iter != m_List.end())
	{
		return iter->second;
	}
	Sound* NewData = new Sound;
	NewData->m_szName = _filename;
	if (NewData)
	{
		br = NewData->Load(m_pSystem, _filename);
		if (br == true)
		{
			m_List.insert(std::make_pair(name, NewData));
		}
	}
	return NewData;
}

bool SoundManager::Release()
{
	for (auto data : m_List)
	{
		Sound* pData = data.second;
		if (pData) pData->Release();
		delete pData;
	}
	m_pSystem->close();
	m_pSystem->release();
	m_List.clear();
	return true;
}

Sound* SoundManager::GetPtr(W_STR _name)
{
	auto iter = m_List.find(_name);
	if (iter != m_List.end())
	{
		Sound* pSound = iter->second;
		return pSound;
	}
	return nullptr;
}
