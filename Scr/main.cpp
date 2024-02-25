#include <thread>
#include <SDL/include/SDL/SDL.h>
#include "VG/VGame.hpp"

int SDL_main(int argc, char* argv[]) {
	VGame * VG = new VGame();
	VG->start();
	while (true)
	{
		VG->update();
		//delay for 1ms to stop the prgram from runing super fast
		SDL_Delay(1);
	}
}