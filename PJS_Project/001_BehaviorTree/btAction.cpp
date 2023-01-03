#include "btAction.h"

void BT::btAction::Reset()
{
    SetStatus(INVAILD);
}

BT::enStatus BT::btAction::Tick()
{
    if (GetStatus() == INVAILD)
    {
        Initalize();
        SetStatus(RUNNING);
    }
    SetStatus(Update());
    if (GetStatus() != RUNNING)
    {
        Terminate();
    }
    return GetStatus();
}
