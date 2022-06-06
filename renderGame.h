#ifndef RENDERGAME_H
#define RENDERGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>

void RenderGame();
void isPlayAgain(bool& quit);
bool About();
bool start();
void resetEverything();
void levelUp();

#endif // RENDERGAME_H
