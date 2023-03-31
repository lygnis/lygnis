#pragma once
#include "MStd.h"
#include "Component.h"
#include "TMath.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	virtual ~TransformComponent();
	void SetPosition(const TVector3& position);
	TVector3 GetPosition();

	void SetRotation(const TVector3& position);
	TVector3 GetRotation();

	void SetScale(const TVector3& position);
	TVector3 GetScale();

	void GetWorldMatrix(TMatrix& mat);

protected:
	void UpdateWorldMatrix();
protected:
	TVector3 positoin_;
	TVector3 rotation_;
	TVector3 scale_ = TVector3(1,1,1);

	TMatrix world_mat_;

};

