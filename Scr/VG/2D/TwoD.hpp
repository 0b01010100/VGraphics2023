#pragma once
#include <Game/VGame.hpp>
class TwoD : public VGame
{
public:
	TwoD();
	void start()override;
	void getUserInput()override;
	void render()override; 
	void update()override;
	void updateQuad();
	VVector2D pos = {  };
};

