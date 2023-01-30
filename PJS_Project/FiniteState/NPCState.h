#pragma once
#include "Npc.h"
class NPCState
{
public:
	Npc* m_pOwner = nullptr;
public:
	virtual void Process() = 0;
	NPCState() = delete;
	NPCState(Npc* npc)
	{
		m_pOwner = npc;
	}
};
class StandState : public NPCState
{
public:
	virtual void Process();
	StandState() = delete;
	StandState(Npc* npc) : NPCState(npc)
	{
	}
};
class MoveState : public NPCState
{
public:
	virtual void Process();
	MoveState() = delete;
	MoveState(Npc* npc) : NPCState(npc)
	{
	}
};

