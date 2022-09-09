#pragma once
#include <math.h>
#define EPSILON 0.0001
struct vePos
{
	union
	{
		struct 
		{
			float x;
			float y;
			float z;

		};
		float v[3];
	};
};

class Vector3D : public vePos
{
public:
	Vector3D operator + (Vector3D& _vec);
	Vector3D operator / (float _fScalar);
	Vector3D operator - (Vector3D& _vec);
	Vector3D operator +=(Vector3D& _vec);
	Vector3D operator *(float _scalar);
	bool operator == (Vector3D& _vec);
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& _vec);
	~Vector3D() {};
public:
	Vector3D Nomalized();
	float Length();
};

