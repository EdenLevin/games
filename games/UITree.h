#ifndef UITREE_H
#define UITREE_H

//#include "edenhagever.h"
#include "SDL.h"
#include "SDL_video.h"
#define BUTTON_X 211
#define BUTTON_Y 50
#define BUTTON_W 218
#define BUTTON_H 32
#define create_UI_button(name,i,delta,prev,parent) create_panel(name,1,BUTTON_X,BUTTON_Y*(i)+delta,BUTTON_W,BUTTON_H,prev,parent)
#define create_game_button(name,i,delta,prev,parent) create_panel(name,1,420,BUTTON_Y*(i)+delta,BUTTON_W,BUTTON_H,prev,parent)

/*contains the brothers and sons of the node*/
struct Node_s {
	struct Button_s			*button;
	struct Node_s			*next;	//next node
	struct Node_s			*prev;	//previous node
};
typedef struct Node_s * Node;

struct linked_list_s {
	Node head;
	Node tail;
};

typedef struct linked_list_s *  linked_list;

struct Button_s{
	char* name;
	int isbutton;
	SDL_Surface* surface;
	//coordinates relative to the father window
	SDL_Rect* rect;
	linked_list sons;
	linked_list parent;
};

typedef struct Button_s * Button;


linked_list UI, current_UI;
SDL_Surface* screen;
SDL_Event e;
char* xy; //temp

/*
*	Initialize the basic variables and settings 
*/
void Initialize_UI();
/*
*	Load all the pictures and build the UI tree
*/
void Load_UI();
/*
*	Drawing all the current UI elements by order
*/
void Draw_UI();
/*
*	No longer has use, might be deleted
*/
Button button_named(char*);
/*
*	Find whether a button of the current UI was pressed, and if so change the UI accordingly
*/
void check_UI(int, int);
/*
*	Check whether x,y are in the button
*/
int ispresssed(Button, int, int);
/*
*	Free the elements of the UI recursively
*/
void free_UI(linked_list);
/*
*	Free the current Node
*/
void free_node(Node);
/*
*	Creates a Node from all the parameters
*/
Node create_panel(char*, int, int, int, int, int, int, Node);

#endif // !UITREE_H