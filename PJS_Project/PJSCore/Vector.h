#pragma once

#include <math.h>
#define PI 3.141592f
#define DegreeToRad(x) (x*(PI/180))
#define RadToDegree(x) (x*(180/PI))
struct Rect
{
	float x0;
	float y0;
	float xSize;
	float ySize;
	float x1;
	float y1;
	float cx;
	float cy;
	Rect() {};
	Rect(float _x, float _y, float w, float h)
	{
		x0 = _x;
		y0 = _y;
		xSize = w;
		ySize = h;
		x1 = x0 + xSize;
		y1 = y0 + ySize;
		cx = (x0 + xSize) / 2;
		cy = (y0 + ySize) / 2;
	}
};
struct Pos2
{
	union
	{
		struct 
		{
			float x;
			float y;
		};
		float v[2];
	};
};

struct Pos3
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
struct Pos4
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};
class Vector2D : public Pos2
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& _vec);
public:
	Vector2D operator + (Vector2D& _vec);
	Vector2D operator - (Vector2D& _vec);
	Vector2D operator * (float _scala);
	Vector2D operator / (float _scala);
	Vector2D operator *= (float _scala);
	Vector2D operator += (Vector2D& _vec);
	Vector2D operator -= (Vector2D& _vec);
	bool      operator == (Vector2D& _vec);
	bool      operator <= (Vector2D& _vec);
	bool      operator >= (Vector2D& _vec);
public:
	float Length();
	Vector2D Normalized();
	float Angle(Vector2D& _vec);
};
class Vector3D : public Pos3
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& _vec);
public:
	Vector3D operator + (Vector3D& _vec);
	Vector3D operator - (Vector3D& _vec);
	Vector3D operator * (float _scala);
	Vector3D operator / (float _scala);
	Vector3D operator *= (float _scala);
	Vector3D operator += (Vector3D& _vec);
	Vector3D operator -= (Vector3D& _vec);
	bool      operator == (Vector3D& _vec);
	bool      operator <= (Vector3D& _vec);
	bool      operator >= (Vector3D& _vec);
public:
	float Length();
	Vector3D Normalized();
	float Angle(Vector3D& _vec);
};

class Vector4D : public Pos4
{
public:
	Vector4D();
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& _vec);
public:
	Vector4D operator + (Vector4D& _vec);
	Vector4D operator - (Vector4D& _vec);
	Vector4D operator * (float _scala);
	Vector4D operator / (float _scala);
	Vector4D operator *= (float _scala);
	Vector4D operator += (Vector4D& _vec);
	Vector4D operator -= (Vector4D& _vec);
	bool      operator == (Vector4D& _vec);
	bool      operator <= (Vector4D& _vec);
	bool      operator >= (Vector4D& _vec);
public:
	float Length();
	Vector4D Normalized();
	float Angle(Vector4D& _vec);
};


