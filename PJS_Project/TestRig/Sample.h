#pragma once
#include "GameCore.h"
#include "Sound.h"
#include"SoundManager.h"
class Sample : public GameCore
{
public:
	Sound*		m_pSound = nullptr;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
};

