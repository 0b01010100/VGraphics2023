#pragma once
#include "Input/inputs.hpp"
#include <map>
class VInputSystem
{
public:
	//check for the desired state of a key
	virtual bool isKey(enum class VKey key, enum class VKeyState state) = 0;
protected:
	//A dictionay the keys track of the current state of a key
	std::map<VKey, VKeyState> keysToCheck;
};

