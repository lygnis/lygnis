#pragma once
#include "Object2D.h"
#include "SpriteManager.h"
enum UIState
{
	UI_NORMAL,
	UI_PUSH,
	UI_STATE,
	UI_MAXSTATE
};
class Button;
class Interface : public Object2D
{
public:
	UIState			m_CurrentState;
public:
	//std::vector<Button*> m_pBtnList;
	//Object2D*		m_pCurrentTex;
public:
	bool Frame() override;
	void SetPosition(Vector2D _pos) override;
	void ScreenToNDC()override;
	void SetActive(bool _Set);
};
class Button : public Interface
{
public:

private:

};

