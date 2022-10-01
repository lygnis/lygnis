#include "MapObject.h"

bool MapObject::Frame()
{
    SetPosition(m_vPosition, m_vCameraPos);
    return true;
}
