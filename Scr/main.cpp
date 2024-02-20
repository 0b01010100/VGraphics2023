#include <thread>
#include <SDL/include/SDL/SDL.h>
#include "VG/VGame.hpp"


#undef main
int main(void) 
{
	VGame * VG = new VGame();
	VG->start();
	while (true)
	{
		VG->update();
		SDL_Delay(1);
	}
}