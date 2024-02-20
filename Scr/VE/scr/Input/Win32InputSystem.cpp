#include <Input/Win32/Win32InputSystem.hpp>

Win32InputSystem::Win32InputSystem()
{
}

bool Win32InputSystem::isKey(enum class VKey key, enum class VKeyState state)
{
	//add the list of key to check for 
	keysToCheck.emplace(std::make_tuple(key, VKeyState::null));
	//check of key is down 
	if (GetAsyncKeyState((int)key)) 
	{
		//set the current key state to down
		keysToCheck[key] = VKeyState::down;
	}
	else 
	{
		//if the key was down before but this time not down
		//Set the current state to key up
		if (keysToCheck[key] == VKeyState::down)
		{
			keysToCheck[key] = VKeyState::up;
		}
		//else if the key was not down set the key state to null
		else
		{
			keysToCheck[key] = VKeyState::null;
		}
	}
	//check if the user's desired key state is equal to the current state of the key
	return (keysToCheck[key] == state);
}

