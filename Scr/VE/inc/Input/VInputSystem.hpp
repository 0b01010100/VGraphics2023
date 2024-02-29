#pragma once
#include "Input/inputs.hpp"
#include <map>
class VInputSystem
{
public:
	//checks for the a key state for the desired key
	virtual bool isKey(enum class VKey key, enum class VKeyState state) = 0;
protected:
	//A dictionay the keys and key state that keeps track of the keys the user is checking for 
	std::map<VKey, VKeyState> keysToCheck;
};

