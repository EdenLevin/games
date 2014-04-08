#include "connect4.h"
#include "edenhagever.h"

#define max1(a,b) ((a)>(b) ? (a): (b))
#define min1(a,b) ((a)<(b) ? (a): (b))


int alphabeta(element elem, int depth, int α, int β,char player,char caller,int* scoring_function(board_t,char)){
	if (depth == 0 || elem->node->edges==NULL)
		return *scoring_function(elem->node->game_state,caller);
    if (caller==player){
		element head= elem->node->edges->head;
		int i;
        //for (head= elem->node->edges->head;head!=NULL;head=head->next){
		for(i=0;i<elem->node->mov_col;i++){
            α = max1(α, alphabeta(connect_create_element(elem,i,player), depth - 1, α, β, player == PLAYER1 ? PLAYER2 : PLAYER1,caller,scoring_function));
            if (β <= α)
                break;
		}
        return α;
	}
    else{
        element head= elem->node->edges->head;
        int i;
        //for (head= elem->node->edges->head;head!=NULL;head=head->next){
		for(i=0;i<elem->node->mov_col;i++){
            β = min1(β, alphabeta(connect_create_element(elem,i,player), depth - 1, α, β, player == PLAYER1 ? PLAYER2 : PLAYER1,caller,scoring_function));
            if (β <= α)
                break;
		}
        return β;
	}
}




////###tictactoe###////

int tictactoe_scoring_func(board_t board, char player)
	{
		//return 1 if player win return -1 if the second player win Otherwise return 0
	int i;
	int score = 0;

	for(i = 0;i<3;i++){
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
				score = board[i][0];
				
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
			score = board[0][i];
	}
	
	if(board[1][1] == board[0][0] && board[1][1] == board[2][2])
			score = board[1][1];
			
	if(board[1][1] == board[0][2] && board[1][1] == board[2][0])
			score = board[1][1];

	if(score==player)
		return 1;
	if(score == -1*player)
		return -1;
	return score;
	}


////###reversi###////

/*scans the board and returns its score*/
int reversi_scoring_func(board_t board, char player){
	int i,j;
	int score = 0;
	int scores[] = { 0, 0, 0, 0, 0 };
	int vector[] = { 1, -1, 5, -5, 10 };
	for (i = 0; i < reversi_ROWS; i++)
	{
		for (j = 0; j < reversi_COLS; j++)
		{
			if ((i==0&&j==0) || (i==0&&j==7) || (i==7&&j==0) || (i==7&&j==7)){	//REGION 5
				if(board[i][j] == player)
					scores[4]++;
			}

			if((i==0&&j==1) || (i==1&&j==0) || (i==1&&j==1) || 
			   (i==0&&j==6) || (i==1&&j==6) || (i==1&&j==7) ||
			   (i==6&&j==0) || (i==6&&j==1) || (i==7&&j==1) || 
			   (i==6&&j==6) || (i==6&&j==7) || (i==7&&j==6)){	//REGION 4
				if(board[i][j] == player)
					scores[3]++;
			}

			if((i==0&&(j>=2&&j<=5)) ||
			   (i==7&&(j>=2&&j<=5)) ||
			   (j==0&&(i>=2&&i<=5)) ||
			   (j==7&&(i>=2&&i<=5))){	//REGION 3
				if(board[i][j] == player)
					scores[2]++;
			}

			if((i==1&&(j>=2&&j<=5)) ||
			   (i==6&&(j>=2&&j<=5)) ||
			   (j==1&&(i>=2&&i<=5)) ||
			   (j==6&&(i>=2&&i<=5))){	//REGION 2
				if(board[i][j] == player)
					scores[1]++;
			}

			if ((i>=2&&i<=5) && (j>=2&&j<=5)){	//REGION 1
				if(board[i][j] == player)
					scores[0]++;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		score += scores[i] * vector[i];
	}
	return score;
}

/*checks whether inserting a disc to this col by this player, leads to his triumph
int reversi_iswinner(board_t board, int col, char player){
	if(moves==64){
		return 1;
	}
	return 0;
}*/


////###connect4###////

/*scans the board and returns its score*/
int connect4_scoring_func(board_t board, char player){
	int score = 0;
	int scores[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int vector[] = { 0, -5, -2, -1, 0, 1, 2, 5, 0 };
	for (int i = 0; i < connect4_ROWS; i++)
	{
		for (int j = 0; j < connect4_COLS; j++)
		{
			if (i < 3){
				scores[count_down(board, i, j, player) + 4]++;
				if (j < 4){
					scores[count_down_right(board, i, j, player) + 4]++;
				}
				if (j>2){
					scores[count_down_left(board, i, j, player) + 4]++;
				}
			}
			if (j < 4){
				scores[count_right(board, i, j, player) + 4]++;
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

/*counts the span to the down*/
int count_down(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += count(board[i + k][j], player);
	return sum;
}

/*counts the span to the right*/
int count_right(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += count(board[i][j + k], player);
	return sum;
}

/*counts the span to the down left*/
int count_down_left(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += count(board[i + k][j - k], player);
	return sum;
}

/*counts the span to the down right*/
int count_down_right(board_t board, int i, int j, char player){
	int sum = 0;
	for (int k = 0; k < 4; k++)
		sum += count(board[i + k][j + k], player);
	return sum;
}

/*an helper function that gives a score of 1 or -1 to a place in the board, according to the player*/
int count(char c, char player){
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

/*checks whether inserting a disc to this col by this player, leads to his triumph*/
int connect4_iswinner(board_t board, int col, char player){
	int i = 0;
	for (int k = 0; k < connect4_ROWS; k++)
	{
		if (board[k][col] != 0){
			i = k;
			break;
		}
	}
	for (int k = 0; k < 4; k++)
	{
		if ((i - k >= 0) && (i - k < 3)){
			if (count_down(board, i - k, col, player) == 4){
				return 1;
			}
			if ((col - k > -1) && (col - k < 4)){
				if (count_down_right(board, i - k, col - k, player) == 4){
					return 1;
				}
			}
			if ((col + k < 7) && (col + k > 2)){
				if (count_down_left(board, i - k, col + k, player) == 4){
					return 1;
				}
			}
		}
		if ((col - k > -1) && (col - k < 4)){
			if (count_right(board, i, col - k, player) == 4){
				return 1;
			}
		}
	}
	return 0;
}
