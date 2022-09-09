#include "CObject.h"

void CObject::SetPosition(float x, float y, float w, float h)
{
	m_rect.Set(x,y,w,h);
	SetCircle(m_rect.o_Px, m_rect.o_Py, m_rect.w, m_rect.h);
}

void CObject::SetCircle(float x, float y, float w, float h)
{
	m_Circle.cx = x;
	m_Circle.cy = y;
	float width = w / 2.0f;
	float height = h / 2.0f;
	m_Circle.fRadius = sqrt(width * width + height * height);
}

void CObject::Frame(float fDeltaTime, float fGameTime)
{

}

void CObject::AddForce(CVector _dir)
{
	m_vForce += _dir;
}

CObject::CObject()
{
	m_rect.Set(20 + (rand() % 80), (20 + rand() % 80), 5.0f+(rand() % 10), 5.0f+(rand() % 10));
	m_vDirection.x = cos(rand());
	m_vDirection.y = sin(rand());
	m_vDirection.Nomalized();
	m_fFriction = 1.0f;
	m_fMass = 100.0f;
	m_fSpeed = 10.0f;
}
