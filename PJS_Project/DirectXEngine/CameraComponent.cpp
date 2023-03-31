#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "World.h"
#include "Game.h"
#include "MGraphicsEngine.h"
CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
	entity_->GetWorld()->GetGame()->GetGraphicsEngine()->RemoveComponent(this);
}

void CameraComponent::GetViewMatrix(TMatrix& view)
{
	entity_->GetTransform()->GetWorldMatrix(view);
	view = view.Invert();
}

void CameraComponent::GetProjectionMatrix(TMatrix& proj)
{
	proj = projection_;
}

void CameraComponent::SetFarPlane(float far_plane)
{
	far_plane_ = far_plane;
	ComputeProjectionMatrix();
}

float CameraComponent::GetFarPlane()
{
	return far_plane_;
}

void CameraComponent::SetNearPlane(float near_plane)
{
	near_plane_ = near_plane;
	ComputeProjectionMatrix();
}

float CameraComponent::GetNearPlane()
{
	return near_plane_;
}

void CameraComponent::SetFieldOfView(float field_of_view)
{
	field_of_view_ = field_of_view;
	ComputeProjectionMatrix();
}

float CameraComponent::GetFieldOfView()
{
	return field_of_view_;
}

void CameraComponent::SetType(const CameraType& type)
{
	type_ = type;
	ComputeProjectionMatrix();
}

CameraType CameraComponent::GetType()
{
	return type_;
}

void CameraComponent::SetScreenArea(const TMath::Rect& area)
{
	screen_area_ = area;
	ComputeProjectionMatrix();
}

TMath::Rect CameraComponent::GetScreenArea()
{
	return screen_area_;
}

void CameraComponent::ComputeProjectionMatrix()
{
	if (type_ == CameraType::PERSPECTIVE)
	{
		projection_ = TMatrix::CreatePerspectiveFieldOfView(field_of_view_,
			(float)screen_area_.width / (float)screen_area_.height, near_plane_, far_plane_);
	}
	else if (type_ == CameraType::ORTHOGONAL)
	{
		projection_ = TMatrix::CreateOrthographic((float)screen_area_.width , (float)screen_area_.height, 
			near_plane_, far_plane_);
	}
}

void CameraComponent::OnCreateInternal()
{
	entity_->GetWorld()->GetGame()->GetGraphicsEngine()->AddComponent(this);
}
