#include "TransformComponent.h"

TransformComponent::TransformComponent()
{

}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::SetPosition(const TVector3& position)
{
	positoin_ = position;
	UpdateWorldMatrix();
}

TVector3 TransformComponent::GetPosition()
{
	return positoin_;
}

void TransformComponent::SetRotation(const TVector3& rotation)
{
	rotation_ = rotation;
	UpdateWorldMatrix();
}

TVector3 TransformComponent::GetRotation()
{
	return rotation_;
}

void TransformComponent::SetScale(const TVector3& scale)
{
	scale_ = scale;
	UpdateWorldMatrix();
}

TVector3 TransformComponent::GetScale()
{
	return scale_;
	UpdateWorldMatrix();

}

void TransformComponent::GetWorldMatrix(TMatrix& mat)
{
	mat = world_mat_;
}

void TransformComponent::UpdateWorldMatrix()
{
	TMatrix temp;
	world_mat_ = TMatrix::Identity;
	temp = TMatrix::Identity;
	temp = TMatrix::CreateScale(scale_);
	world_mat_ = world_mat_*temp;

	temp = TMatrix::Identity;
	temp = TMatrix::CreateRotationX(rotation_.x);
	world_mat_ = world_mat_ * temp;

	temp = TMatrix::Identity;
	temp = TMatrix::CreateRotationY(rotation_.y);
	world_mat_ = world_mat_ * temp;

	temp = TMatrix::Identity;
	temp = TMatrix::CreateRotationZ(rotation_.z);
	world_mat_ = world_mat_ * temp;

	temp = TMatrix::Identity;
	temp.Translation(positoin_);
	world_mat_ = world_mat_ * temp;
}
