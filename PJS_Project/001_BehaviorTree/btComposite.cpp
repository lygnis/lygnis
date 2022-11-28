#include "btComposite.h"

BT::btNode* BT::btComposite::GetChild(int index)
{
    return listChild_[index];
}

int BT::btComposite::GetChildCount()
{
    return listChild_.size();
}

void BT::btComposite::AddChild(btNode* newChild)
{
    newChild->SetIndex(listChild_.size());
    newChild->SetParent(this);
    listChild_.push_back(newChild);
}

void BT::btComposite::Reset()
{
    for (int i = 0; i < listChild_.size(); i++)
    {
        GetChild(i)->Reset();
    }
}
