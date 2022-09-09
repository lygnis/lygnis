#pragma once
#include "Vector3D.h"
#include "Matrix4X4.h"


struct Box
{
	Vector3D v_ctPoint;				// ¿øÁ¡ controll Point
	Vector3D v_Size;					// ³ÐÀÌ
};

struct Coor : public Box
{
	Vector3D v_edPoint;				// ³¡Á¡
	Vector3D v_Center;				// Áß¾ÓÁ¡
	Coor() {};
	Coor(Vector3D _min, Vector3D _size)
	{
		SetPosition(_min, _size);
	}
	~Coor() {};
public:
	bool operator == (Coor& _coor);
	void SetPosition(Vector3D _min, Vector3D _size)
	{
		v_ctPoint = _min;
		v_Size = _size;
		this->v_edPoint = _min + _size;
		Vector3D v_Temp = v_ctPoint + v_edPoint;
		this->v_Center = v_Temp / 2.0f;
		return;
	}
};

enum CollisionType
{
	BoxOut,
	BoxOverLap,
	BoxIn
};

class Collision
{
public:
	Collision() {};
	~Collision() {};

public:
	static CollisionType BoxToBox(Coor& _a, Coor& _b);

};
