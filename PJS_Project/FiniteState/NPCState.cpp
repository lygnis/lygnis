#include "NPCState.h"

void StandState::Process()
{
	std::cout << "Stand \n";
	if (rand() % 2 == 0)
	{
		m_pOwner->SetTransition(EVENT_TIMEMOVE);
		std::cout << "changeState Movement\n";
	}
}

void MoveState::Process()
{
	std::cout << "Move\n";
	if (rand() % 2 == 0)
	{
		m_pOwner->SetTransition(EVENT_STOPMOVE);
		std::cout << "Move Stop\n";
	}
}
