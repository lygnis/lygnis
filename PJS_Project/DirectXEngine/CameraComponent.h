#pragma once
#include "MStd.h"
#include "Component.h"
#include "DX3D/Math/Rect.h"
#include "TMath.h"
class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual~CameraComponent();

	void GetViewMatrix(TMatrix& view);
	void GetProjectionMatrix(TMatrix& proj);

	void SetFarPlane(float far_plane);
	float GetFarPlane();

	void SetNearPlane(float near_plane);
	float GetNearPlane();

	void SetFieldOfView(float field_of_view);
	float GetFieldOfView();

	void SetType(const CameraType& type);
	CameraType GetType();

	void SetScreenArea(const TMath::Rect& area);
	TMath::Rect GetScreenArea();
private:
	void ComputeProjectionMatrix();
protected:
	virtual void OnCreateInternal();
private:
	TMatrix projection_;


	float near_plane_ = 0.01f;
	float far_plane_ = 1000.0f;
	float field_of_view_ = 1.3f;

	CameraType type_ = CameraType::PERSPECTIVE;
	// 화면의 영역
	TMath::Rect screen_area_;

};

