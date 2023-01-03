#include "btSelector.h"

BT::enStatus BT::btSelector::Update()
{
    for (int i = 0; i < GetChildCount(); ++i)
    {
        enStatus enCurrStatus = GetChild(i)->Tick();
        if (enCurrStatus != FAILURE)
        {
            ClearChild(i);
            return enCurrStatus;
        }
    }
    return FAILURE;
}

void BT::btSelector::ClearChild(int Index)
{
    for (int i = 0; i < GetChildCount(); ++i)
    {
        if (i != Index)
            GetChild(i)->Reset();
    }
}
