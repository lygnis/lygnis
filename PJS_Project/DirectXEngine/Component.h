#pragma once
#include "MStd.h"
class Component
{
public:
	Component();
	virtual~Component();

	void Release();
	Entity* GetEntity();
protected:
	virtual void OnCreateInternal();
protected:
	size_t type_ID_ = 0;
	Entity* entity_ = nullptr;
private:
	friend class Entity;
};

