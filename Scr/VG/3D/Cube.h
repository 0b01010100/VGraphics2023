#pragma once
#include <Game/VGame.hpp>
class Cube : public VGame
{
public:
	//called on the start of the game 
	void start() override;
	//get input from the user
	void getUserInput() override;
	//render the whole secne
	void render() override;
	//update cube transform data
	void updateCube();
	//update the game
	void update() override;
	//rotation of the cube on the X and Y
	VVector2D rot = {  };
	//scale of the cube on the X and Y
	VVector2D scale = { 2, 2};

	class D3D11ConstantBuffer* cb;
	class D3D11VertexBuffer* vb;
	class D3D11IndexBuffer* ib;

	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
};

