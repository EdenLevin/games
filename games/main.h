#ifndef MAIN_H
#define MAIN_H

#define SCREEN_W 640
#define SCREEN_H 480
#include "UITree.h"

/*
*	The gameloop that calls Update() and Draw()
*/
int main(int, char**);
/*
*	Initialize the basic variables and settings
*/
void Initialize();
/*
*	Load all content of the program
*/
void Load_Content();
/*
*	Handles all the program updates.
*	The most important function in all the program.
*/
void Update();
/*
*	Handles the all the draw calls
*/
void Draw();
/*
*	Handles the exit of the program
*/
void Quit();

#endif // !MAIN_H