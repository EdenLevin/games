#include "UITree.h"

/*
*	Initialize the basic variables and settings
*/
void Initialize_UI(){	
	//The UI tree
	UI = (linked_list)malloc(sizeof(struct linked_list_s));	

	//The x and y coordinates at the top of the screen
	xy = (char*)malloc(sizeof(char)*20); //temp
}

/*
*	Load all the pictures and build the UI tree
*/
void Load_UI(){
	//NEED NULL CHECKS FOR MALLOCS

	Node head;
	Node node_incharge;
	linked_list UI_incharge;
	linked_list sons;
	int i = 1;
	int delta = 90;

	//The main menu screen
	head = create_panel("main_panel", 0, 0, 0, 640, 480, NULL, NULL);
	UI->head = head;

	head = create_UI_button("new_game_button", i++, delta, head, NULL);

	head = create_UI_button("load_game_button", i++, delta, head, NULL);

	head = create_UI_button("quit_button", i++, delta, head, NULL);
	head->next = NULL;
	UI->tail = head;

	//The new game screen
	node_incharge = UI->head->next;//new-game node
	UI_incharge = UI;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("connect4_button", i++, delta, head, UI_incharge);

	head = create_UI_button("TTT_button", i++, delta, head, UI_incharge);

	head = create_UI_button("reversi_button", i++, delta, head, UI_incharge);

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The load game screen
	node_incharge = UI->head->next->next;//load-game node
	UI_incharge = UI;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("connect4_button", i++, delta, head, UI_incharge);

	head = create_UI_button("TTT_button", i++, delta, head, UI_incharge);

	head = create_UI_button("reversi_button", i++, delta, head, UI_incharge);

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The new game of Connect4 screen, need more UI elements
	node_incharge = UI->head->next->button->sons->head->next;//new-game Connect4 node
	UI_incharge = UI->head->next->button->sons;
	i = 1;
	delta = 905;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The new game of TTT screen, need more UI elements
	node_incharge = UI->head->next->button->sons->head->next->next;//new-game TTT node
	UI_incharge = UI->head->next->button->sons;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("TTT_board", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_game_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The new game of Reversi screen, need more UI elements
	node_incharge = UI->head->next->button->sons->head->next->next->next;//new-game Reversi node
	UI_incharge = UI->head->next->button->sons;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The load game of Connect4 screen, need more UI elements
	node_incharge = UI->head->next->next->button->sons->head->next;//load-game Connect4 node
	UI_incharge = UI->head->next->next->button->sons;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The load game of TTT screen, need more UI elements
	node_incharge = UI->head->next->next->button->sons->head->next->next;//load-game TTT node
	UI_incharge = UI->head->next->next->button->sons;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;

	//The load game of Reversi screen, need more UI elements
	node_incharge = UI->head->next->next->button->sons->head->next->next->next;//load-game Reversi node
	UI_incharge = UI->head->next->next->button->sons;
	i = 1;
	delta = 90;
	sons = (linked_list)malloc(sizeof(struct linked_list_s));

	head = create_panel("select_game_panel", 0, 0, 0, 640, 480, NULL, UI_incharge);
	sons->head = head;

	head = create_UI_button("cancel_button", i++, delta, head, UI_incharge);
	head->next = NULL;
	sons->tail = head;
	node_incharge->button->sons = sons;
}

/*
*	Drawing all the current UI elements by order
*/
void Draw_UI(){
	Node head;
	//Drawing all the current UI elements by order
	for (head = current_UI->head; head != NULL; head = head->next){
		if (head != NULL)
			SDL_BlitSurface(head->button->surface, NULL, screen, head->button->rect);
	}
}

/*
*	No longer has use, might be deleted
*/
Button button_named(char* name){
	Node head;
	for (head = current_UI->head; head != NULL; head = head->next)
	{
		if (!strcmp(head->button->name, name))
			return head->button;
	}
}

/*
*	Find whether a button of the current UI was pressed, and if so change the UI accordingly
*/
void check_UI(int x, int y){
	Node head;
	for (head = current_UI->head; head != NULL; head = head->next)
	{
		if (ispresssed(head->button, x, y)){
			if (current_UI->tail == head)
				if (head->button->parent == NULL)
					exit(0);
				else
					current_UI = head->button->parent;
			else
				current_UI = head->button->sons;
			return;
		}
	}
}

/*
*	Check whether x,y are in the button
*/
int ispresssed(Button button, int x, int y){
	return ((x >= button->rect->x) && (x <= button->rect->x + button->rect->w) &&
		(y >= button->rect->y) && (y <= button->rect->y + button->rect->h) &&
		button->isbutton);
}

/*
*	Free the elements of the UI recursively
*/
void free_UI(linked_list ui){
	Node head, next;
	for (head = ui->head; head != NULL; head = next)
	{
		next = head->next;
		if (head->button->sons != NULL)
			free_UI(head->button->sons);
		free_node(head);
	}
	free(ui);
}

/*
*	Free the current Node
*/
void free_node(Node node){	
	SDL_FreeSurface(node->button->surface);
	free(node->button->rect);
	free(node->button);
	free(node);
}

/*
*	Creates a Node from all the parameters
*/
Node create_panel(char* name, int isbutton, int x, int y, int w, int h, Node prev, linked_list parent){
	//NEED NULL CHECKS FOR MALLOCS

	Node node = (Node)malloc(sizeof(struct Node_s));
	Button button = (Button)malloc(sizeof(struct Button_s));
	SDL_Surface *surface = (SDL_Surface *)malloc(sizeof(SDL_Surface));
	SDL_Rect *rect = (SDL_Rect *)malloc(sizeof(SDL_Rect));
	char* fullname = (char*)malloc(sizeof(char)* 100);
	sprintf(fullname, "../pics/%s.bmp", name);
	surface = SDL_LoadBMP(fullname);
	button->surface = surface;
	button->name = name;
	button->isbutton = isbutton;
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	button->rect = rect;
	button->parent = parent;
	button->sons = NULL;
	node->button = button;
	node->prev = prev;
	if (prev != NULL)
		prev->next = node;
	return node;
}
