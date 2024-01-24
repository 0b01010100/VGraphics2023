#pragma once
class VWorld
{
public:
	VWorld ( class VGame* game );
	void Start ( );
	void Update ( );
	class VGame* m_game;
};

