#pragma once
#include "MStd.h"
#include <map>

class Entity
{
public:
	Entity();
	virtual ~Entity();
	void Release();


	World* GetWorld();
	TransformComponent* GetTransform();

	template <typename T>
	T* CreateComponent()
	{
		auto c = GetComponent<T>();
		if (!c)
		{
			// 엔티티 유형 T에 대한 고유 식별자를 검색
			auto id = typeid(T).hash_code();
			auto c = new T();
			CreateComponentInternal(c, id);
			return c;
		}
		return nullptr;
	}
	template <typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component Class");
		// 엔티티 유형 T에 대한 고유 식별자를 검색
		auto id = typeid(T).hash_code();
		return (T*)GetComponentInternal(id);
	}
private:
	void CreateComponentInternal(Component* component, size_t id);
	Component* GetComponentInternal(size_t id);
	void RemoveComponent(size_t id);
protected:
	virtual void OnCreate() {}
	virtual void OnUpdate(float delta_time) {}
protected:
	size_t type_ID_ = 0;
	World* world_ = nullptr;
	TransformComponent* transform_ = nullptr;

	std::map<size_t, std::unique_ptr<Component>> components_;
	friend class World;
	friend class Component;
};