/*
  This file contains all the functions
  Required for a multiplayer(1 Vs 1) Gameplay

  */

#include <stdio.h>
#include <string.h>
#include "funcs.h"



void select_user();
void printBoard(char *board);
void makeboard();
int takeTurn(char *board, int player, const char*);
int checkWin(char *board);
int checkFour(char *board, int, int, int, int);
int horizontalCheck(char *board);
int verticalCheck(char *board);
int diagonalCheck(char *board);
/*
  Called when Multiplayer is Selected
*/
void onStartMulti(){
  char board[rows][columns];
    select_user();
}
void select_user(){

  printUsers();
  p1:{

    char nm[20];
    char dummy[1];
    gets(dummy);
    printf("Select the Player 1: ");
    gets(nm);
    int check = checkUser(nm);

    if(!check){
      printf("User Not Found");
      goto p1;
    }
    else{
        strcpy(current[0].name,nm);
    }
  }
  p2:
  {
  char nm[20];
  printf("Select the Player 2: ");
  gets(nm);
  int check = checkUser(nm);
  if(!check){
    printf("User Not Found");
    goto p2;
  }
  else{
      strcpy(current[1].name,nm);
  }
}

}

void makeboard(char *board[rows][columns]){
    for(int i=0;i<rows;i++){
      for(int j=0;j<columns;j++){
        board[i][j] = ' ';
      }
    }
}
