#include "StateMachine.h"
#include "Npc.h"

int main()
{
	StateMachine fsm;
	fsm.AddTransition(STATE_STAND, EVENT_TIMEMOVE, STATE_MOVE);
	fsm.AddTransition(STATE_STAND, EVENT_FINDTARGET, STATE_ATTACK);
	fsm.AddTransition(STATE_MOVE, EVENT_STOPMOVE, STATE_STAND);
	fsm.AddTransition(STATE_ATTACK, EVENT_LOSTTARGET, STATE_STAND);

	Npc npc(&fsm);
	std::cout << "Hello World!\n";
	while (1)
	{
		npc.Process();
		Sleep(1000);
	}
	return 0;
}