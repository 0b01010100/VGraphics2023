#include <thread>
#include <SDL/include/SDL/SDL.h>
#include "VG/2D/TwoD.hpp"

int SDL_main(int argc, char* argv[]) {
	TwoD* VG = new TwoD();
	VG->start();
	while (true)
	{
		VG->update();
		//delay for 1ms to stop the prgram from runing super fast
		SDL_Delay(1);
	}
}