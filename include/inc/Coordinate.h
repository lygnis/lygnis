#pragma once
#include "TStd.h"
#include "Vector.h"



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
	static CollisionType BoxToBox(Rect& _a, Rect& _b);

};
