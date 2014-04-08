#include "main.h"

/*
*	The gameloop that calls Update() and Draw()
*/
int main(int argc, char* args[]){
	Initialize();
	Load_Content();
	current_UI = UI;
	printf("%s\n", UI->head->button->name);
	while (1){
		Update();
		Draw();

		SDL_Delay(100);
	}
	return 0;
}

/*
*	Initialize the basic variables and settings
*/
void Initialize(){
	//NEED NULL CHECKS FOR MALLOCS

	//Easy to handle exit event by quit() function
	atexit(Quit);

	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set up screen
	screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

	Initialize_UI();
}

/*
*	Load all content of the program
*/
void Load_Content(){
	Load_UI();
}

/*
*	Handles all the program updates.
*	The most important function in all the program.
*/
void Update(){
	while (SDL_PollEvent(&e) != 0) {

		//Set the x and y coordinates at the top of the screen
		sprintf(xy, "%d, %d", e.button.x, e.button.y); //temp
		SDL_WM_SetCaption(xy, "SDL Test"); //temp

		switch (e.type)
		{
		case SDL_QUIT:
			//Exit the game
			exit(0);
			break;

		case SDL_MOUSEBUTTONDOWN:
			//Mouse click detected
			check_UI(e.button.x, e.button.y);
			break;

		default:
			break;
		}
	}
}

/*
*	Handles the all the draw calls
*/
void Draw(){
	//Clear the screen
	SDL_FillRect(screen, 0, 0);
	
	Draw_UI();

	//The actual draw
	SDL_Flip(screen);
}

/*
*	Handles the exit of the program
*/
void Quit(){
	//Free the UI tree
	free_UI(UI);

	//Free the loaded image
	SDL_FreeSurface(screen);

	//Quit SDL
	SDL_Quit();
}


