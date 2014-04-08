#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<stdarg.h>

#define TTT_ROWS 3 /* # of rows in board  */
#define TTT_COLS 3 /* # of columns in board  */

#define connect4_ROWS 6 /* # of rows in board  */
#define connect4_COLS 7 /* # of columns in board  */

#define reversi_ROWS 8 /* # of rows in board  */
#define reversi_COLS 8 /* # of columns in board  */


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

int isDigit(char);

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


/*checks whether the string is only white spaces*/
int only_whitespaces(char * str)
{
	char *p = str;
	while (*p != '\0'){
		if (!isspace((int)(*(p++))))
			return 0;
	}
	return 1;
}


int isDigit(char s);
int valid_connect4(board_t board, int col);
void initialize_board_connect4();

//tictactoe scoring function
int tictactoe_scoring_func(board_t board, char player);

//reversi scoring function
int reversi_iswinner(board_t board, int col, char player);
int reversi_scoring_func(board_t board, char player);

//connect4 scoring function
int connect4_scoring_func(board_t board, char player);
int count_down(board_t, int, int, char);
int count_right(board_t, int, int, char);
int count_down_right(board_t, int, int, char);
int count_down_left(board_t, int, int, char);
int count(char, char);
int connect4_iswinner(board_t board, int col, char player);