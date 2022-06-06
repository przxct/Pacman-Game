#include "renderGame.h"
#include "externVariables.h"
#include "creatWallandPoint.h"

void RenderGame()
{

    //Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    //Render walls
    for (int i = 1; i <= NUMBER_WALLS; i++)
        SDL_RenderDrawRect(gRenderer, &walls[i]);

    //Render background
    background.render(0, 0);

    //Render cherry
    for (int i = 1; i <= 4; i++) {
        if (cherryX[i] == -1 && cherryY[i] == -1) continue;
        sprites.render(cherryX[i], cherryY[i], &cherry);
    }

    //Render points
    for (int rowi = 1; rowi <= NUMBER_ROW; rowi++)
        for (int coli = 1; coli <= NUMBER_COL; coli++)
            if (!isEateanPoint[rowi][coli])
                sprites.render(pointX[rowi][coli], pointY[rowi][coli], &point);

    bool resetghosts = pacman.isDead;

    //Render Pacman
    pacman.render();
    
    //Render Ghosts
    for (int i = 1; i <= 4; i++)
        if (ghosts[i].timeDeath == -1) {
            if (resetghosts && pacman.mPosX == 20 && pacman.mPosY == 20) {
                ghosts[i].resetGhost();
            }
            ghosts[i].render(i - 1);
        }

    //Score
    SDL_Color textColor = { 255, 255, 255 };
    Text.loadFromRenderedText("SCORE", textColor);
    Text.renderText(30);
    Text.loadFromRenderedText(to_string(Score), textColor);
    Text.renderText(80);

    //Lives
    Text.loadFromRenderedText("LIVES", textColor);
    Text.renderText(180);
    Text.loadFromRenderedText(to_string(pacman.Lives), textColor);
    Text.renderText(230);

    //Level
    Text.loadFromRenderedText("LEVEL", textColor);
    Text.renderText(330);
    Text.loadFromRenderedText(to_string(Level), textColor);
    Text.renderText(380);

    //Update screen
    SDL_RenderPresent( gRenderer );
}

void resetEverything()
{
    //Create Walls
    createWalls();
    createPoint();

    //Create Pacman & Ghost Animation & Point
    getPacmanAnimation();
    getGhostAnimation();

    //Reset frames and score
    frames = 0;
    Score = 0;
    Level = 1;

    //Reset ghosts and pacman
    pacman.reset();
    pacman.direct = 0;
    pacman.Lives = 3;
    pacman.isDead = false;
    pacman.eatCherry = false;
    pacman.timeEatCherry = 0;

    for (int i = 1; i <= NUMBER_GHOSTS; i++)
        ghosts[i].resetGhost();

    //Play opening music
    RenderGame();
    Mix_PlayChannel(1, opening, 0);

    while (Mix_Playing(1) != 0) {
        SDL_Delay(200);
    }

    //Play theme music
    //Mix_PlayMusic( theme, -1 );
}

void levelUp()
{
    //Create Walls
    createWalls();
    createPoint();

    //Create Pacman & Ghost Animation & Point
    getPacmanAnimation();
    getGhostAnimation();

    //Reset ghosts and pacman
    pacman.reset();
    pacman.direct = 0;
    pacman.isDead = false;
    pacman.eatCherry = false;
    pacman.timeEatCherry = 0;

    for (int i = 1; i <= NUMBER_GHOSTS; i++)
        ghosts[i].resetGhost();

    //Play opening music
    RenderGame();
    Mix_PlayChannel(1, opening, 0);

    while (Mix_Playing(1) != 0) {
        SDL_Delay(200);
    }
}

void isPlayAgain(bool& quit)
{
    SDL_Event e;
    while(true)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_KEYDOWN)
            {
                switch( e.key.keysym.sym )
                {
                    case SDLK_y:
                    {
                        quit = false;
                        resetEverything();
                        return;
                    }
                    case SDLK_n:
                    {
                        return;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );
        gameOver.render(0, 0);
        SDL_Color textColor = { 255, 255, 255 };
        Text.loadFromRenderedText("Press Y to play again!", textColor);
        Text.render(250, 620);
        Text.loadFromRenderedText("Press N to exit game!", textColor);
        Text.render(260, 700);
        SDL_RenderPresent( gRenderer );
    }
}
bool About(){
    SDL_Event e;
    int xMouse, yMouse;
    while (true)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch (e.type){
                case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_GetMouseState(&xMouse,&yMouse);
                    if (yMouse > 750 && yMouse < 800 && xMouse > 370 && xMouse < 750){     // Back Button
                        return true;
                    }
                    else continue;
                }
                case SDL_QUIT:
                {
                    return false;
                }
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );
        AboutBackground.render(0, 0);
        SDL_GetMouseState(&xMouse,&yMouse);
        if (yMouse > 750 && yMouse < 800 && xMouse > 370 && xMouse < 750)
            BackButtonLight.render(370, 750);
        else
            BackButton.render(370, 750);
        SDL_RenderPresent( gRenderer );
    }
}
bool start(){
    SDL_Event e;
    int xMouse, yMouse;
    while(true)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            switch (e.type){
                case SDL_MOUSEBUTTONDOWN:
                {
                    SDL_GetMouseState(&xMouse,&yMouse);
                    if (yMouse > 650 && yMouse < 700 && xMouse > 370 && xMouse < 750){     // Start Button
                        return true;
                    }
                    if (yMouse > 730 && yMouse < 780 && xMouse > 370 && xMouse < 750){     // About Button
                        if (!About())
                            return false;
                        else continue;
                    }
                    else continue;
                }
                case SDL_QUIT:
                {
                    return false;
                }
            }
        }
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255 );
        SDL_RenderClear( gRenderer );
        Introduce.render(0, 0);
        SDL_GetMouseState(&xMouse,&yMouse);
        if (yMouse > 650 && yMouse < 700 && xMouse > 370 && xMouse < 750)
            StartButtonLight.render(370, 650);
        else
            StartButton.render(370, 650);
        if (yMouse > 730 && yMouse < 780 && xMouse > 370 && xMouse < 750)
            AboutButtonLight.render(370, 730);
        else
            AboutButton.render(370, 730);
        SDL_RenderPresent( gRenderer );
    }
}