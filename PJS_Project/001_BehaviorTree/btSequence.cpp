#include "btSequence.h"

BT::enStatus BT::btSequence::Update()
{
    enStatus enCurrStatus = INVAILD;
    for (int i = 0; i < GetChildCount(); i++)
    {
        enCurrStatus = GetChild(i)->GetStatus();
        if (GetChild(i)->GetNodeType() != ACTION || GetChild(i)->GetStatus() != SUCCESS)
            enCurrStatus = GetChild(i)->Tick();
        if (enCurrStatus != SUCCESS)
            return enCurrStatus;
    }
    return SUCCESS;
}
