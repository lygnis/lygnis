#pragma once
#include "MStd.h"
#include <map>
#include <set>
class World
{
public:
	World(Game* game);
	~World();
	// ����ڰ� ��� ������ ��ƼƼ�� ����� �ְ� ���ø� �Լ��� �����Ѵ�.
	// �߰��Ϸ��� ��ƼƼ ������ �����ϴ� ���ø� �Ű������� �ϳ��� ���
	template <typename T>
	T* CreateEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity Class");
		// ��ƼƼ ���� T�� ���� ���� �ĺ��ڸ� �˻�
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
	// �����Ϸ��� ��ƼƼ Ŭ���� ������ ���� �ĺ���
	std::map<size_t, std::map<Entity*, std::unique_ptr<Entity>>> entities_;
	std::set<Entity*> entitiesToDestory;
	Game* game_ = nullptr;
	friend class Entity;
};

