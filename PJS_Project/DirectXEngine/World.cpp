#include "World.h"
#include "Entity.h"

World::World(Game* game): game_(game)
{
}

World::~World()
{
}

void World::Update(float delta_time)
{
	for (auto e : entitiesToDestory)
	{
		entities_[e->type_ID_].erase(e);
	}
	entitiesToDestory.clear();
	for (auto&& [typeID, entities] : entities_)
	{
		for (auto&& [ptr, entity] : entities)
		{
			ptr->OnUpdate(delta_time);
		}
	}
}

Game* World::GetGame()
{
	return game_;
}

void World::CreateEntityInternal(Entity* entity, size_t id)
{
	auto entityPtr = std::unique_ptr<Entity>(entity);
	entities_[id].emplace(entity, std::move(entityPtr));
	entity->type_ID_ = id;
	entity->world_ = this;
	entity->OnCreate();
}

void World::RemoveEntity(Entity* entity)
{
	entitiesToDestory.emplace(entity);
}
 