#include "connect4.h"


/*int main(){
	initialize_connect_board();
	connect_gameloop();
	return 0;
}*/



void connect_gameloop(){
	connect_moves = 0;
	char command_line[NUM_CHAR + 2];
	int printboard = 1;
	connect_newgame = 1;
	connect_gameover = 0;
	while (1){
		if ((printboard) && (!connect_gameover)){
			connect_printBoard(connect_mainBoard);
		}
		if ((connect_moves == 42) && (!connect_gameover)){
			connect_gameover = 1;
			printf("Game over: board is full\n");
		}
		/* This function reads up to sizeof(fullcommand)-1 characters,
		or until it encounters the new line character.
		The function adds '\0' to the end of the array */
		if (fgets(command_line, sizeof(command_line), stdin) == NULL)
		{
			perror("Error: standard function fgets has failed"); /* error case */
			break; /* breaks the while(1) loop */
		}
		int action = connect_handle_input(command_line);
		switch (action)
		{
		case ANOTHER_COMMAND:
			printboard = 0;
			break;
		case NEXT_TURN:
			printboard = 1;
			connect_moves += 2;
			break;
		case RESTART:
			connect_moves = 0;
			connect_gameover = 0;
			printboard = 1;
			connect_restart_game();
			break;
		case QUIT:
			connect_quit();
			break;
		}
	}
}

int connect_handle_input(char *command_line){
	/* # of characters (excluding '\n') in command_line is <=num_char iff the condition takes place. */
	if (command_line[sizeof(command_line)-2] != '\n'&&strlen(command_line) == NUM_CHAR + 1)
	{
		printf("Error: command length must be less than or equal to %d characters\n", NUM_CHAR);
		while (getchar() != '\n'){} /* read the remaining characters */
		return ANOTHER_COMMAND;/* continue with  while(1) loop */
	}
	/* Checks that command-line is composed only from whitespace characters */
	if (connect_only_whitespaces(command_line))
	{
		printf("Error: line command must have at least one non-whitespace character\n");
		return ANOTHER_COMMAND; /* continue with  while(1) loop */
	}

	if (strncmp(command_line, "quit", 4) == 0){
		return QUIT;
	}

	if (strncmp(command_line, "restart_game", 12) == 0){
		return RESTART;
	}
	if (connect_newgame){
		if (!((strncmp(command_line, "set_number_steps", 16) == 0) && connect_isDigit(command_line[17])))   {
			printf("Error: first command must be set_number_steps\n");	/*error 4*/
			return ANOTHER_COMMAND;
		}
		else
		{
			if (command_line[17] - '0' == 0){
				printf("Error: number of minimax steps must be non-zero\n");	/*error 5*/
			}
			else if (command_line[17] - '0' > 7){
				printf("Error: cannot set number of steps - too many steps\n");	/*error 10*/
			}
			else{
				connect_treedepth = (command_line[17]) - '0';
				connect_newgame = 0;
			}
			return ANOTHER_COMMAND;
		}
	}
	if ((strncmp(command_line, "set_number_steps", 16) == 0) && connect_isDigit(command_line[17])){           //we need to add more checks,,,,17 or 16???
		if (command_line[17] - '0' == 0)
			printf("Error: number of minimax steps must be non-zero\n");	/*error 5*/
		else if (command_line[17] - '0' > 7)
			printf("Error: cannot set number of steps - too many steps\n");	/*error 10*/


		connect_treedepth = (command_line[17]) - '0';
		return ANOTHER_COMMAND;

	}
	if ((strncmp(command_line, "suggest_move", 12) == 0)){
		if (connect_gameover){
			printf("Error: game is over\n");
		}
		else{
			connect_suggest_move();
		}
		return ANOTHER_COMMAND;
	}
	if ((strncmp(command_line, "add_disc", 8) == 0) && connect_isDigit(command_line[9])){           //we need to add more checks,,,,,9 or 8???
		if (connect_isDigit(command_line[9]) != 2){
			printf("Error: column number must be in range 1-7\n");	/*error 6*/
			return ANOTHER_COMMAND;
		}
		else if (!connect_valid(connect_mainBoard, command_line[9] - '0' - 1)){
			printf("Error: column %c is full\n", command_line[9]);
			return ANOTHER_COMMAND;
		}
		else if (connect_gameover){
			printf("Error: game is over\n");
			return ANOTHER_COMMAND;
		}
		else{
			connect_add_disc(command_line[9] - '0');
			return NEXT_TURN;
		}
	}
	return RESTART;
}

/*sets the tree depth to be the number of steps*/
void connect_set_number_steps(int num_steps){
	connect_treedepth = num_steps;
}

/*prints the suggested move to the user,according to the minimax algorithm*/
void connect_suggest_move(){
	int col = connect_minimax(PLAYER1);
	printf("Suggested move: add disc to column %d\n", col + 1);
}

/*adds a disc to the appropriate column according to the user's input,
*and then runs the minimax algorithm to add the computer's disc, and prints the computer's move.
*/
void connect_add_disc(int col_num){
	int iswinner = connect_put(col_num - 1, PLAYER1);
	if (iswinner == WINNER){
		connect_printBoard(connect_mainBoard);
		printf("Game over: you win\n");
		connect_gameover = 1;
		return;
	}
	int col = connect_minimax(PLAYER2);
	iswinner = connect_put(col, PLAYER2);
	printf("Computer move: add disc to column %d\n", col + 1);
	if (iswinner == WINNER){
		connect_printBoard(connect_mainBoard);
		printf("Game over: computer wins\n");
		connect_gameover = 1;
	}
}

/*quit the game*/
void connect_quit(){
	connect_free_board(connect_mainBoard);
	exit(0);
}

/*initialize the board*/
void initialize_connect_board(){
	connect_mainBoard = (char**)malloc(CONNECT4_ROWS*sizeof(char *));
	for (int i = 0; i < CONNECT4_ROWS; ++i){
		connect_mainBoard[i] = (char*)calloc(CONNECT4_COLS, sizeof(char));
	}
}

/*starts a new game*/
void connect_restart_game(){
	printf("Game restarted\n");
	initialize_connect_board();
}

/*checks whether the string is only white spaces*/
int connect_only_whitespaces(char * str)
{
	char *p = str;
	while (*p != '\0'){
		if (!isspace((int)(*(p++))))
			return 0;
	}
	return 1;
}

/*prints the board */
void connect_printBoard(board_t board){
	for (int i = 0; i < CONNECT4_ROWS; i++) {
		printf("%c ", '|');
		for (int j = 0; j < CONNECT4_COLS; j++) {
			if (board[i][j] == 0)
				printf("%c", ' ');
			else
				printf("%c", board[i][j]);
			printf("%c", ' ');
		}
		printf("%c", '|');
		printf("\n");
	}

	printf("-----------------");
	printf("\n");
	printf("  1 2 3 4 5 6 7  \n");

}

void connect_free_minimax(element elem){
	linked_list sons = elem->node->edges;
	element node = sons->head;
	while (node != NULL){
		element temp = node;
		node = node->next;
		connect_free_minimax(temp);
	}
	connect_free_element(elem);
}

void connect_free_element(element elem){
	connect_free_board(elem->node->game_state);
	free(elem->node->edges);
	free(elem->node);
	free(elem);
}

void connect_free_board(board_t board){
	for (int i = 0; i < CONNECT4_ROWS; i++)
	{
		free(board[i]);
	}
	free(board);
}

// 0-6 convention
int connect_put(int col, char player){
	for (int i = CONNECT4_ROWS - 1; i >= 0; i--)
	{
		if (connect_mainBoard[i][col] == 0){
			connect_mainBoard[i][col] = player;
			return connect_iswinner(connect_mainBoard, col, player) ? WINNER : ORDINARY;
		}
	}
	return 0;
}

int connect_iswinner(board_t board, int col, char player){
	int i = 0;
	for (int k = 0; k < CONNECT4_ROWS; k++)
	{
		if (board[k][col] != 0){
			i = k;
			break;
		}
	}
	for (int k = 0; k < 4; k++)
	{
		if ((i - k >= 0) && (i - k < 3)){
			if (connect_count_down(board, i - k, col, player) == 4){
				return 1;
			}
			if ((col - k > -1) && (col - k < 4)){
				if (connect_count_down_right(board, i - k, col - k, player) == 4){
					return 1;
				}
			}
			if ((col + k < 7) && (col + k > 2)){
				if (connect_count_down_left(board, i - k, col + k, player) == 4){
					return 1;
				}
			}
		}
		if ((col - k > -1) && (col - k < 4)){
			if (connect_count_right(board, i, col - k, player) == 4){
				return 1;
			}
		}
	}
	return 0;
}

int connect_scoring_func(board_t board, char player){
	int score = 0;
	int scores[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int vector[] = { 0, -5, -2, -1, 0, 1, 2, 5, 0 };
	for (int i = 0; i < CONNECT4_ROWS; i++)
	{
		for (int j = 0; j < CONNECT4_COLS; j++)
		{
			if (i < 3){
				scores[connect_count_down(board, i, j, player) + 4]++;
				if (j < 4){
					scores[connect_count_down_right(board, i, j, player) + 4]++;
				}
				if (j>2){
					scores[connect_count_down_left(board, i, j, player) + 4]++;
				}
			}
			if (j < 4){
				scores[connect_count_right(board, i, j, player) + 4]++;
			}
		}
	}
	if (scores[8] != 0){
		return 100000;
	}
	if (scores[0] != 0){
		return -100000;
	}
	for (int i = 0; i < 9; i++)
	{
		score += scores[i] * vector[i];
	}
	return score;
}

int connect_count_down(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += connect_count(board[i + k][j], player);
	return sum;
}

int connect_count_right(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += connect_count(board[i][j + k], player);
	return sum;
}

int connect_count_down_left(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += connect_count(board[i + k][j - k], player);
	return sum;
}

int connect_count_down_right(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += connect_count(board[i + k][j + k], player);
	return sum;
}

/**/
int connect_count(char c, char player){
	if (player == PLAYER1){
		if (c == PLAYER1)
			return 1;
		if (c == PLAYER2)
			return -1;
	}
	else{
		if (c == PLAYER2)
			return 1;
		if (c == PLAYER1)
			return -1;
	}
	return 0;
}

int connect_isDigit(char s){
	if (s == '1' || s == '2' || s == '3' || s == '4' || s == '5' || s == '6' || s == '7')
		return 2;
	if (s == '0' || s == '8' || s == '9'){
		return 1;
	}
	return 0;
}

// 0-6 convention
int connect_valid(board_t board, int col){
	return board[0][col] == 0 ? 1 : 0;
}

element connect_create_element(element elem, int col, char player){
	int updated = 0;
	board_t newBoard = (char**)malloc(CONNECT4_ROWS*sizeof(char*));
	for (int i = CONNECT4_ROWS - 1; i >= 0; i--)
	{
		newBoard[i] = (char*)calloc(CONNECT4_COLS, sizeof(char));
		for (int j = 0; j < CONNECT4_COLS; j++)
		{
			char value = elem->node->game_state[i][j];
			newBoard[i][j] = value;
			if ((j == col) && (value == 0) && (!updated)){
				updated = 1;
				newBoard[i][j] = player;
			}
		}

	}
	vertex newVertex = (vertex)malloc(sizeof(struct vertex_s));
	newVertex->game_state = newBoard;
	newVertex->mov_col = col;
	element newElement = (element)malloc(sizeof(struct element_s));
	newElement->node = newVertex;
	return newElement;
}

int connect_minimax(char player){
	vertex v = (vertex)malloc(sizeof(struct vertex_s));
	board_t newBoard = (char**)malloc(CONNECT4_ROWS*sizeof(char*));
	for (int i = CONNECT4_ROWS - 1; i >= 0; i--)
	{
		newBoard[i] = malloc(CONNECT4_COLS*sizeof(char));
		for (int j = 0; j < CONNECT4_COLS; j++)
		{
			newBoard[i][j] = connect_mainBoard[i][j];
		}
	}
	v->game_state = newBoard;
	element elem = (element)malloc(sizeof(struct element_s));;
	elem->node = v;
	connect_minimax_build(elem, connect_treedepth, player, player,&connect_scoring_func);
	int value = connect_minimax_scores(elem, MAXIMIZE, player);
	int col = 0;
	linked_list sons = elem->node->edges;
	for (element son = sons->head; son != NULL; son = son->next){
		if (value == son->node->score){
			col = son->node->mov_col;
			break;
		}
	}
	connect_free_minimax(elem);
	return col;
}

void connect_minimax_build(element parent, int depth, char player, char caller,int* (scoring_func)(board_t b,char c)){
	parent->node->edges = (linked_list)malloc(sizeof(struct linked_list_s));
	parent->node->edges->head = (element)malloc(sizeof(struct element_s));
	parent->node->edges->tail = (element)malloc(sizeof(struct element_s));
	parent->node->edges->head = NULL;
	parent->node->edges->tail = NULL;
	if (depth == 0){ // a leaf
		parent->node->score = *scoring_func(parent->node->game_state, caller);
		return;
	}
	for (int i = 0; i < CONNECT4_COLS; i++)
	{
		if (connect_valid(parent->node->game_state, i)){
			element child = connect_create_element(parent, i, player);
			child->next = (element)malloc(sizeof(struct element_s));
			child->next = NULL;
			if (parent->node->edges->head == NULL){
				parent->node->edges->head = child;
				parent->node->edges->tail = child;
			}
			else{
				element temp = parent->node->edges->tail;
				parent->node->edges->tail = child;
				temp->next = child;
			}
			if (connect_iswinner(child->node->game_state, i, player)){ // create a leaf
				connect_minimax_build(child, 0, player == PLAYER1 ? PLAYER2 : PLAYER1, caller,scoring_func);
			}
			else{
				connect_minimax_build(child, depth - 1, player == PLAYER1 ? PLAYER2 : PLAYER1, caller, scoring_func);
			}
		}
	}
}

int connect_minimax_scores(element elem, int maximize, char player){
	linked_list children = elem->node->edges;
	if (children->head == NULL){ // a leaf
		return elem->node->score;
	}
	int bestvalue;
	if (maximize == MAXIMIZE){
		/*
		* search for the biggest child
		*/
		bestvalue = -1000000;
		for (element child = children->head; child != NULL; child = child->next){
			int value = connect_minimax_scores(child, MINIMIZE, player);
			if (value > bestvalue){
				bestvalue = value;
			}
		}
	}
	else{
		/*
		* search for the smallest child
		*/
		bestvalue = 1000000;
		for (element child = children->head; child != NULL; child = child->next){
			int value = connect_minimax_scores(child, MAXIMIZE, player);
			if (value < bestvalue){
				bestvalue = value;
			}
		}
	}
	elem->node->score = bestvalue;
	return bestvalue;
}
