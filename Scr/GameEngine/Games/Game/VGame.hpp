#pragma once
#include <GraphicsEngine/PlatformSpec/req/D3D.hpp>
#include "VWorld.hpp"

class VGame
{
public:
	VGame ( );
	void Start ( );
	void Update ( );
public:
	HWND m_hwnd;


};

