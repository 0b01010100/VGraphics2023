#include <Games/Game/VGame.hpp>
#include <SDL/SDL.h>
#undef main
int main ( void )
{
    VGame game = {};
    game.Start ( );
    while ((true))
	{
        SDL_Delay ( 3 );
        game.Update ( );
	}
    return 0;
}


