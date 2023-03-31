#include "Entity.h"
#include "World.h"
#include "Component.h"
#include "TransformComponent.h"
Entity::Entity()
{
	transform_ = CreateComponent<TransformComponent>();
}

Entity::~Entity()
{

}

void Entity::Release()
{
	world_->RemoveEntity(this);
}


World* Entity::GetWorld()
{
	return world_;
}

TransformComponent* Entity::GetTransform()
{
	return transform_;
}

void Entity::CreateComponentInternal(Component* component, size_t id)
{
	auto componentPtr = std::unique_ptr<Component>(component);
	components_.emplace(id, std::move(componentPtr));
	component->type_ID_ = id;
	component->entity_ = this;

	component->OnCreateInternal();
}

Component* Entity::GetComponentInternal(size_t id)
{
	auto it = components_.find(id);
	if (it == components_.end())
		return nullptr;
	return it->second.get();
}

void Entity::RemoveComponent(size_t id)
{
	components_.erase(id);
}
