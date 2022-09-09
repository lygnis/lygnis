#pragma once
#include <math.h>
#define Pi 3.141592
#define DegreeToRad Pi/180
#define RadToDegree 180/Pi
struct veDir
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
class Vector3D : public veDir
{
public:
	float m_fAngle;
	float m_fLength;
public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	~Vector3D() {};
public:
	float GetLength(float _x, float _y, float _z);
	Vector3D Nomalized(Vector3D& _vec);
	float DotVector(const Vector3D& _vec);			//³»Àû
	Vector3D OuterProduct(const Vector3D& _vec);
	float BetweenAngelVec(const Vector3D& _vec);
	//float GetAngle(float _x, float _y);
public:
	Vector3D operator + (Vector3D& _vec);
	Vector3D operator * (float _scalar);
	Vector3D operator - (Vector3D& _vec);
	
};

