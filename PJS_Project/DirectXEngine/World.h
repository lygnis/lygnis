#pragma once
#include "MStd.h"
#include <map>
#include <set>
class World
{
public:
	World(Game* game);
	~World();
	// 사용자가 모든 종류의 엔티티를 만들수 있게 템플릿 함수로 구현한다.
	// 추가하려는 엔티티 유형을 정의하는 템플릿 매개변수는 하나만 사용
	template <typename T>
	T* CreateEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity Class");
		// 엔티티 유형 T에 대한 고유 식별자를 검색
		auto id = typeid(T).hash_code();
		auto e = new T();
		CreateEntityInternal(e, id);
		return e;
	}
	void Update(float delta_time);
	Game* GetGame();
private:
	void CreateEntityInternal(Entity* entity, size_t id);
	void RemoveEntity(Entity* entity);
private:
	// 저장하려는 엔티티 클래스 유형의 고유 식별자
	std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> entities_;
	std::set<Entity*> entitiesToDestory;
	Game* game_ = nullptr;
	friend class Entity;
};

