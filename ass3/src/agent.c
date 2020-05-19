
/***********************************************************************
 *  Student ID: z5196042 
 *  This program is written by Joshua Zobule using agent.c (written by
 *  Alan Blair) as the starting point.
 *
 *  
 *  This program is an agent that plays the game - 9 board tic_tac_toe.
 *  The algorithms used in this program is the Minimax algorithm with alpha beta pruning.
 *  I was not able to construct a data structure so I used the provided 
 *  board[10][10]. Since I was not able to construct a data structure like a tree, everytime 
 *  minimax is called, there is an extra parameter called board_num which specifies
 *  which board or tile the player is in at that moment to search. 
 *   
 *  minimax() performs the minimax algorithm and it uses three helper 
 *  functions; evaluate, minimum and maximum. evaluate() evaluates the
 *  current board and returns a score if it is a terminal node. minimum()
 *  returns the smallest value of two values and maximum() returns
 *  the largest value of two values. Both minimum() and maximum() help 
 *  minimax() with computation. The alpha and beta parameters in
 *  minimax() help prune the tree where needed so that it reduces the time
 *  it takes to search. When performing the minimax algorithm, the output
 *  seemed to perform the same move repeatedly for some reason which results in a loss.
 *  Hence, in minimax(), before storing the best move, I made the agent search
 *  through the array of moves to make sure that it  is not the same as 
 *  the previous move it made.
 *   
 */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "common.h"
#include "agent.h"
#include "game.h"

#define MAX_MOVE 81

#define TRUE    1
#define FALSE   0

#define DEPTH   9
#define INFINITY 1000

int board[10][10];
int move[MAX_MOVE+1];
int player;
int m;


// Struct state holds information about a state
// which are the best move and corresponding payoff value
typedef struct {
    int move;
    int score;
} state;

int minimum(int a, int b) {
    if (a < b) return a;
    
    return b;
}

int maximum(int a, int b) {
    if (a > b) return a;
    
    return b;
}

// returns TRUE if a specified board is filled and no more moves can be played
int no_more_moves(int board[10][10], int board_num) {
    for (int i = 1; i < 10; i++) 
        if (board[board_num][i] == EMPTY) return FALSE;
    
    return TRUE;
}

// This function evaluates each state. It returns 10 if the agent has won 
// in that state, returns -10 if the opponent has one that state and 
// returns 0 if none of the players have won
int evaluate(int board[10][10], int board_num) {
    
    // cases in which a player wins a row in a board
    for (int row = 1; row < 10; row = row + 3) {
        if (board[board_num][row] == board[board_num][row + 1] && 
            board[board_num][row + 1] == board[board_num][row + 2]) {
            
            if (board[board_num][row] == player) return 10;
            else if (board[board_num][row] != player && 
                     board[board_num][row] != EMPTY) 
                     return -10;
        }
    }
    
    // cases in which a player wins a column in a board
    for (int col = 1; col < 4; col++) {
        if (board[board_num][col] == board[board_num][col + 3] && 
            board[board_num][col + 3] == board[board_num][col + 6]) {
            
            if (board[board_num][col] == player) return 10;
            else if (board[board_num][col] != player && 
                     board[board_num][col] != EMPTY) 
                     return -10;
        }
    }
    
    // cases in which a player wins diagonally:
    // Diagonal case 1
    if (board[board_num][1] == board[board_num][5] && 
        board[board_num][5] == board[board_num][9]) {
    
        if (board[board_num][1] == player) return 10;
        else if (board[board_num][1] != player && 
                 board[board_num][1] != EMPTY) 
                 return -10;
    }
    // Diagonal case 2
    if (board[board_num][3] == board[board_num][5] && 
        board[board_num][5] == board[board_num][7]) {
    
        if (board[board_num][3] == player) return 10;
        else if (board[board_num][3] != player && 
                 board[board_num][3] != EMPTY) 
                 return -10;
    }
    
    return 0;
}

// This function performs the Minimax algorithim with alpha beta pruning
// and returns a struct called state which holds information about 
// the state such as the best move and the corresponding payoff value
state minimax(int board[10][10], int depth, int alpha, int beta, 
              int whose_turn, int board_num) {
              
    int score = evaluate(board, board_num);
    
    if (depth == 0 || score == 10 || score == -10) {
        state result;
        result.score = score;
        return result;
    }
    
    if (no_more_moves(board, board_num) == TRUE) {
        state result;
        result.score = 0;
        return result;
    } 
    
    if (whose_turn == player) { 
        int bestMax = -INFINITY;
        int bestMove = -1;
        for (int i = 1; i < 10; i++) {
            if (board[board_num][i] == EMPTY) {
                board[board_num][i] = player; // temporarily set move
                
                int branch = minimax(board, depth - 1, alpha, 
                                     beta, !player, i).score;
                                     
                bestMax = maximum(bestMax, branch);
                
                // store move of best score when that move is not the same 
                // as the previous move made by agent
                if (bestMax == branch && i != move[m - 2]) bestMove = i; 
                board[board_num][i] = EMPTY; // undo the move
                
                alpha = maximum(alpha, branch);
                if (alpha >= beta) break; // pruning
                
            }
        }
        state result;
        result.move = bestMove;
        result.score = bestMax;
        return result;
    
    } else { 
        int bestMin = INFINITY;
        for (int j = 1; j < 10; j++) {
            if (board[board_num][j] == EMPTY) {
                board[board_num][j] = !player; // temporarily set move
                
                int branch = minimax(board, depth - 1, alpha, 
                                     beta, player, j).score;
                                     
                bestMin = minimum(bestMin, branch);
                board[board_num][j] = EMPTY; // undo move
                
                beta = minimum(beta, branch);
                if (beta <= alpha) break; // pruning
            }
        }
        state result;
        result.score = bestMin;
        return result;
    }
}

/*********************************************************//*
   Print usage information and exit
*/
void usage( char argv0[] )
{
  printf("Usage: %s\n",argv0);
  printf("       [-p port]\n"); // tcp port
  printf("       [-h host]\n"); // tcp host
  exit(1);
}

/*********************************************************//*
   Parse command-line arguments
*/
void agent_parse_args( int argc, char *argv[] )
{
  int i=1;
  while( i < argc ) {
    if( strcmp( argv[i], "-p" ) == 0 ) {
      if( i+1 >= argc ) {
        usage( argv[0] );
      }
      port = atoi(argv[i+1]);
      i += 2;
    }
    else if( strcmp( argv[i], "-h" ) == 0 ) {
      if( i+1 >= argc ) {
        usage( argv[0] );
      }
      host = argv[i+1];
      i += 2;
    }
    else {
      usage( argv[0] );
    }
  }
}

/*********************************************************//*
   Called at the beginning of a series of games
*/
void agent_init()
{
  struct timeval tp;

  // generate a new random seed each time
  gettimeofday( &tp, NULL );
  srandom(( unsigned int )( tp.tv_usec ));
}

/*********************************************************//*
   Called at the beginning of each game
*/
void agent_start( int this_player )
{
  reset_board( board );
  m = 0;
  move[m] = 0;
  player = this_player;
}

/*********************************************************//*
   Choose second move and return it
*/
int agent_second_move( int board_num, int prev_move )
{
  int this_move;
  move[0] = board_num;
  move[1] = prev_move;
  board[board_num][prev_move] = !player;
  m = 2;
  do {
    this_move = minimax(board, DEPTH, -INFINITY, 
                        INFINITY, player, prev_move).move;
                        
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  //printf("SECOND MOVE:\nboard_num is %d\nprev_move is %d\nAI move is %d\n\n", board_num, prev_move, this_move);
  board[prev_move][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Choose third move and return it
*/
int agent_third_move(
                     int board_num,
                     int first_move,
                     int prev_move
                    )
{
  int this_move;
  move[0] = board_num;
  move[1] = first_move;
  move[2] = prev_move;
  board[board_num][first_move] =  player;
  board[first_move][prev_move] = !player;
  m=3;
  do {
  
    this_move = minimax(board, DEPTH, -INFINITY, 
                        INFINITY, player, prev_move).move;
                        
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  //printf("THIRD MOVE:\nboard_num is %d\nprev_move is %d\nAI move is %d\n\n", board_num, prev_move, this_move);
  board[move[m-1]][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Choose next move and return it
*/
int agent_next_move( int prev_move )
{
  int this_move;
  m++;
  move[m] = prev_move;
  board[move[m-1]][move[m]] = !player;
  m++;
  do {
  
    this_move = minimax(board, DEPTH, -INFINITY, 
                        INFINITY, player, prev_move).move;
                        
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  //printf("NEXT MOVE:\nprev_move is %d\nAI move is %d\n\n", prev_move, this_move);
  board[move[m-1]][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Receive last move and mark it on the board
*/
void agent_last_move( int prev_move )
{
  m++;
  move[m] = prev_move;
  board[move[m-1]][move[m]] = !player;
}

/*********************************************************//*
   Called after each game
*/
void agent_gameover(
                    int result,// WIN, LOSS or DRAW
                    int cause  // TRIPLE, ILLEGAL_MOVE, TIMEOUT or FULL_BOARD
                   )
{
  // nothing to do here
}

/*********************************************************//*
   Called after the series of games
*/
void agent_cleanup()
{
  // nothing to do here
}
