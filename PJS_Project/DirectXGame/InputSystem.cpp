#include "InputSystem.h"
#include <Windows.h>

std::shared_ptr<InputSystem> InputSystem::_system = nullptr;

void InputSystem::Update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	if (_first_time)
	{
		_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		_first_time = false;
	}

	if (current_mouse_pos.x != _old_mouse_pos._x || current_mouse_pos.y != _old_mouse_pos._y)
	{
		// 마우스 움직였을때 이벤트
		std::unordered_set<InputListener*>::iterator it = _set_listeners.begin();

		while (it != _set_listeners.end())
		{
			(*it)->OnMouseMove(Point(current_mouse_pos.x - _old_mouse_pos._x , current_mouse_pos.y - _old_mouse_pos._y));
			++it;
		}
	}
	_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(_keys_state))
	{
		for (UINT i = 0; i < 256; i++)
		{
			// 키 DOWN
			if (_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = _set_listeners.begin();

				while (it != _set_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (_keys_state[i] != _old_keys_state[i]) 
						{
							(*it)->OnLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
					}
					else if (i == VK_RBUTTON)
					{
						if (_keys_state[i] != _old_keys_state[i])
						{
							(*it)->OnRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
					}
					else
					{
						(*it)->onKeyDown(i);
					}
					(*it)->onKeyDown(i);
					++it;
				}
			}
			// 키 UP
			else
			{
				if (_keys_state[i] != _old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = _set_listeners.begin();

					while (it != _set_listeners.end())
					{
						if (i == VK_LBUTTON)
							(*it)->OnLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else if (i == VK_RBUTTON)
							(*it)->OnRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						else
							(*it)->onKeyUp(i);
						(*it)->onKeyUp(i);
						++it;
					}
				}
			}
		}
		// store current keys state to old key state buffer
		::memcpy(_old_keys_state, _keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	// 리스너 제거
	_set_listeners.erase(listener);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}

void InputSystem::Create()
{
	if (InputSystem::_system) throw std::exception("InputSystem already created");
	InputSystem::_system = std::make_shared<InputSystem>();
}

void InputSystem::Release()
{
	if (!InputSystem::_system) return;
}