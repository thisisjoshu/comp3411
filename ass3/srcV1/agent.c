/*********************************************************
 *  agent.c
 *  Nine-Board Tic-Tac-Toe Agent
 *  COMP3411/9414/9814 Artificial Intelligence
 *  Alan Blair, CSE, UNSW
 */
 

/********************************************************
 *  This program is written by Joshua Zobule using agent.c (written by
 *  Alan Blair) as the starting point.
 *  
 *  Student ID: z5196042
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

int board[10][10];
int move[MAX_MOVE+1];
int player;
int m;

int minimum(int a, int b) {
    if (a < b) return a;
    
    return b;
}

int maximum(int a, int b) {
    if (a > b) return a;
    
    return b;
}

int no_more_moves(int board[10][10], int board_num){
    for (int i = 1; i < 10; i++) 
        if (board[board_num][i] == EMPTY) return FALSE;
    
    return TRUE;
}

int evaluate(int board[10][10], int board_num) {
    
    // row wins
    for (int row = 1; row < 10; row = row + 3) {
        if (board[board_num][row] == board[board_num][row + 1] && 
            board[board_num][row + 1] == board[board_num][row + 2]) {
            
            if (board[board_num][row] == player) return 10;
            else if (board[board_num][row] != player && board[board_num][row] != EMPTY) return -10;
        }
    }
    
    // column wins
    for (int col = 1; col < 4; col++) {
        if (board[board_num][col] == board[board_num][col + 3] && 
            board[board_num][col + 3] == board[board_num][col + 6]) {
            
            if (board[board_num][col] == player) return 10;
            else if (board[board_num][col] != player && board[board_num][col] != EMPTY) return -10;
        }
    }
    
    // diagonal wins
    
    if (board[board_num][1] == board[board_num][5] && board[board_num][5] == board[board_num][9]) {
        if (board[board_num][1] == player) return 10;
        else if (board[board_num][1] != player && board[board_num][1] != EMPTY) return -10;
    }
    
    if (board[board_num][3] == board[board_num][5] && board[board_num][5] == board[board_num][7]) {
        if (board[board_num][3] == player) return 10;
        else if (board[board_num][3] != player && board[board_num][3] != EMPTY) return -10;
    }
    
    return 0;
}

int minimax(int board[10][10], int depth, int whose_turn, int board_num) {
    int score = evaluate(board, board_num);
    
    if (score == 10) return score;
    
    if (score == -10) return score;
    
    if (no_more_moves(board, board_num) == TRUE) return 0;
    
    if (whose_turn == 1) { 
        int bestMax = -1000;
        
        for (int i = 1; i < 10; i++) {
            for (int j = 1; j < 10; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = player;
                    bestMax = maximum(bestMax, minimax(board, depth + 1, 0, i));
                    board[i][j] = EMPTY;
                }
            }
        }
        
        return bestMax;
    
    } else if (whose_turn == 0) { 
        int bestMin = 1000;
        
        for (int i = 1; i < 10; i++) {
            for (int j = 1; j < 10; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = !player;
                    bestMin = minimum(bestMin, minimax(board, depth + 1, 1, i));
                    board[i][j] = EMPTY;
                }
            }
        }
        return bestMin;
    }
}

int start_move(int board[10][10]) {
    int move_value;
    int best_value = -1000;
    int move = 1; 
    
    //printf("im in start_move right now!\n");
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = player;
                move_value = minimax(board, 0, 0, i);
                
                if (move_value > best_value) {
                    best_value = move_value;
                    move = j;
                }
                
                board[i][j] = EMPTY;
            }
        }
    }
    
    return move;    
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
    this_move = start_move(board);
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  printf("AI move is %d\n", this_move);
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
    this_move = start_move(board);
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  printf("AI move is %d\n", this_move);
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
    this_move = start_move(board);
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  printf("AI move is %d\n", this_move);
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
