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
        bool isPause = false;

        resetEverything();
        while( !quit )
        {
            //Handle Events from keyboard
            //cout << isPause << " " << pacman.mPosX << " " << pacman.mPosY << " " << pacman.mVelX << " " << pacman.mVelY << '\n';
            bool previousPause = isPause;
            handleEvent(quit, isPause);

            if (quit)
                break;
            
            if (!isPause && !previousPause) 
            {
                //Handle motion and collision
                Motion_Collision(quit);

                //Render Game
                if (!quit) 
                {
                    RenderGame();
                }
                else
                {
                    Mix_HaltMusic();
                    isPlayAgain(quit);
                }
            }
            else RenderGame();
        }
    }

	//Free resources and close SDL
	close();
	return 0;
}
