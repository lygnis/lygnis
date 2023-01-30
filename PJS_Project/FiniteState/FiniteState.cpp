#include "FiniteState.h"

void FiniteState::AddTransition(DWORD dwEvent, DWORD outState)
{
    _State[dwEvent] = outState;
}

DWORD FiniteState::GetTransition(DWORD dwEvent)
{
    return _State[dwEvent];
}
