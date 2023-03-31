#include "MeshComponent.h"
#include "Entity.h"
#include "World.h"
#include "Game.h"
#include "MGraphicsEngine.h"
MeshComponent::MeshComponent()
{
}

MeshComponent::~MeshComponent()
{
	entity_->GetWorld()->GetGame()->GetGraphicsEngine()->RemoveComponent(this);
}

void MeshComponent::SetMesh(const MeshPtr& mesh)
{
	mesh_ = mesh;
}

const MeshPtr& MeshComponent::GetMesh()
{
	return mesh_;
}

void MeshComponent::AddMaterial(const MaterialPtr& material)
{
	materials_.push_back(material);
}

void MeshComponent::RemoveMaterial(int index)
{
	if (index >= materials_.size())
		return;
	materials_.erase(materials_.begin() + index);
}

const std::vector<MaterialPtr>& MeshComponent::GetMaterials()
{
	return materials_;
}

void MeshComponent::OnCreateInternal()
{
	entity_->GetWorld()->GetGame()->GetGraphicsEngine()->AddComponent(this);
}
