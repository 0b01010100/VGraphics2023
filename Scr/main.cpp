#include <thread>
#include <SDL/include/SDL/SDL.h>
#include "VG/3D/Cube.h"

int SDL_main(int argc, char* argv[]) {
	Cube* VG = new Cube();
	VG->start();
	while (true)
	{
		VG->update();
		//delay for 1ms to stop the prgram from runing super fast
		SDL_Delay(1);
	}
}