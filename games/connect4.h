#ifndef CONNECT4_H
#define CONNECT4_H


#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<stdarg.h>

#define CONNECT4_ROWS 6 /* # of rows in board  */
#define CONNECT4_COLS 7 /* # of columns in board  */
#define NUM_CHAR 40 /* # of characters in command  */
#define ANOTHER_COMMAND 1  // output for the handle_input
#define NEXT_TURN 2  // output for the handle_input
#define RESTART 3  // output for the handle_input
#define QUIT 4  // output for the handle_input
#define ORDINARY 1 // output for put function
#define WINNER 2 // output for put function
#define MAXIMIZE 1 // a parameter for minimax
#define MINIMIZE 2 // a parameter for minimax
#define PLAYER1 'O' // represent the player
#define PLAYER2 'X' // represent the computer



/*a struct that represents the vertex*/
struct element_s {
	struct vertex_s		*node;
	struct element_s	*next;
};

typedef struct element_s *  element;
typedef char** board_t;

/*a struct that represents the sons as a linked list*/
struct linked_list_s {
	element head;
	element tail;
};

typedef struct linked_list_s *  linked_list;

/*a struct that represents the sub vertex*/
struct vertex_s {
	unsigned int	mov_col;
	board_t			game_state;
	int				score;

	linked_list		edges;
};

typedef struct  vertex_s * vertex;


int isDigit(char s);
int valid_connect4(board_t board, int col);
void initialize_board_connect4();

//connect4 scoring function
int connect4_scoring_func(board_t board, char player);
int count_down(board_t, int, int, char);
int count_right(board_t, int, int, char);
int count_down_right(board_t, int, int, char);
int count_down_left(board_t, int, int, char);
int count(char, char);
int connect4_iswinner(board_t board, int col, char player);



int connect_newgame;
int connect_gameover;
int connect_treedepth;
int connect_moves;
board_t connect_mainBoard;

/*
* Prototypes
*/
void connect_gameloop(void);
void connect_suggest_move(void);
void connect_add_disc(int);
void connect_quit(void);
void connect_initialize_board(void);
void connect_restart_game(void);
void connect_printBoard(board_t);
void connect_free_minimax(element);
void connect_free_board(board_t);
int connect_only_whitespaces(char * str);
int connect_put(int, char);
int connect_iswinner(board_t, int, char);
int connect_scoring_func(board_t, char);
int connect_count_down(board_t, int, int, char);
int connect_count_right(board_t, int, int, char);
int connect_count_down_right(board_t, int, int, char);
int connect_count_down_left(board_t, int, int, char);
int connect_count(char, char);
int connect_isDigit(char);
int connect_valid(board_t, int);
element connect_create_element(element, int, char);
int connect_minimax(char);
void connect_minimax_build(element, int, char, char);
int connect_minimax_scores(element, int, char);
int connect_handle_input(char*);
void connect_free_element(element);
void connect_free_minimax(element);

#endif // !CONNECT4_H