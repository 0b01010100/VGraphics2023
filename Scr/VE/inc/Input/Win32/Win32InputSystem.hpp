#pragma once
#include <Input/VInputSystem.hpp>

class Win32InputSystem : public VInputSystem
{
public:
	Win32InputSystem();
	bool isKeyOfCode(enum class Win32Input);

	bool isKey(VKey key, VKeyState state) override;
};

