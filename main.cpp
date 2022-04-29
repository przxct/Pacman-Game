#include "LTexture.h"
#include "pacman.h"
#include "creatWallandPoint.h"
#include "InitCloseSDL.h"
#include "externVariables.h"
#include "renderGame.h"
#include "Motion_Collision.h"

using namespace std;

int main( int argc, char* args[] )
{
    srand(time(NULL));

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
		return 0;
	}
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return 0;
    }
    //Load sound
    if( !loadSound() )
    {
        printf( "Failed to load music!\n" );
        return 0;
    }


    //Game loop
    if (start())
    {
        //Main loop flag
        bool quit = false;

        resetEverything();
        while( !quit )
        {
            //Handle Events from keyboard
            handleEvent(quit);

            //Handle motion and collision
            Motion_Collision(quit);

            //Render Game
            RenderGame();

            if (quit == true)
            {
                Mix_HaltMusic();
                isPlayAgain(quit);

            }
        }
    }

	//Free resources and close SDL
	close();
	return 0;
}
