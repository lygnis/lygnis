#include "Component.h"
#include "Entity.h"
Component::Component()
{
}

Component::~Component()
{
}

void Component::Release()
{
	entity_->RemoveComponent(type_ID_);
}

Entity* Component::GetEntity()
{
	return entity_;
}

void Component::OnCreateInternal()
{

}
