#pragma once
#include <math.h>
#include <windows.h>
#define EPSILON 0.0001
#define PI 3.141592f
#define RadianToDgree(x) (x*(PI/180))
#define DgreeToRadian(x) (x*(180/PI))
struct tFloat
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

// ∫§≈Õ º≥¡§
class CVector :public tFloat
{
public:
	CVector();
	CVector(float x, float y);
	CVector(const CVector& _vector);
	//~CVector();
public:
	CVector operator + (CVector& _vector);
	CVector operator - (CVector& _vector);
	CVector operator * (float _scalar);
	CVector operator +=(CVector& _vector);
	CVector operator / (float _scalar);
	CVector operator *=(float _scalar);
	bool operator == (CVector& _vector);
public:
	float PrevLength();
	float Length();					// ∫§≈Õ ±Ê¿Ã
	CVector Nomalized();				// ¥‹¿ß∫§≈Õ
	float Angle(CVector& _vec);		// ∫§≈Õ ≥ª¿˚»ƒ cos(ceta) ∞¢
};

