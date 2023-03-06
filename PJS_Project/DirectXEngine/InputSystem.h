#pragma once
#include "InputListener.h"
#include <unordered_set>
#include "Point.h"
#include <memory>
class InputSystem
{
public:
	InputSystem() {};
	~InputSystem() {};
public:
	void Update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
public:
	static InputSystem* get();
	static void Create();
	static void Release();
private:
	std::unordered_set<InputListener*> _set_listeners;
	unsigned char _keys_state[256] = {};
	unsigned char _old_keys_state[256] = {};
	Point _old_mouse_pos;
	bool _first_time = true;
	static std::shared_ptr<InputSystem> _system;
};

