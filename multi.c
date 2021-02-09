/*
  This file contains all the functions
  Required for a multiplayer(1 Vs 1) Gameplay

  */

#include <stdio.h>
#include <string.h>
#include "funcs.h"

int rows =6;
int columns =7;
void select_user();
void printBoard();
void makeBoard();
int takeTurn(int player, const char*);
int checkWin();
int checkFour(int, int, int, int,int,int,int,int);
int horizontalCheck();
int verticalCheck();
int diagonalCheck();
void bringDown(int, int);
/*
  Called when Multiplayer is Selected
*/

void bringDown(int row, int col){

}
int takeTurn(int player, const char *PIECES)
{
  printf("Player %d (%c):\nEnter number coordinate: ", player + 1, PIECES[player]);
  int col=0,row=0;
  while(1)
  {
     if(1 != scanf("%d", &col) || col < 1 || col > 7 )
     {
        while(getchar() != '\n');
        puts("Number out of bounds! Try again.");
     }
     else
     {
        break;
     }
  }
  col--;

   for(row =5;row>=0;row--)
   {
     if(board[row][col]==' ')
     {
       board[row][col]= PIECES[player];
       return 1;
     }
   }
  return 0;
}

void onStartMulti()
{
  const char *PIECES = "XO";
    select_user();
    makeBoard();
    int turn=0,done=0;
    for(turn = 0; turn <rows*columns && !done; turn++)
    {
       system("cls");
       printBoard();
       while(!takeTurn(turn % 2,PIECES))
       {
          printBoard();
          puts("\n**Column full!**\n");
       }
       done = checkWin();
    }
    system("cls");
    printBoard();

    if(turn == rows*columns && !done)
    {
      puts("\nIts a Tie");
    }
    else
    {
      turn--;
      printf("Player %d (%c) wins !\n",turn % 2 + 1, PIECES[turn%2]);
    }
}

void select_user()
{
  printUsers();
  p1:
  {
    char nm[20];
    char dummy[1];
    gets(dummy);
    printf("Select the Player 1: ");
    gets(nm);
    int check = checkUser(nm);

    if(!check)
    {
      printf("User Not Found");
      goto p1;
    }
    else
    {
        strcpy(current[0].name,nm);
    }
  }

  p2:
  {
  char nm[20];
  printf("Select the Player 2: ");
  gets(nm);
  int check = checkUser(nm);
  if(!check)
  {
    printf("User Not Found");
    goto p2;
  }
  else
  {
      strcpy(current[1].name,nm);
  }
}

}

int checkWin()
{
    return (horizontalCheck() || verticalCheck() || diagonalCheck());

}
int checkFour(int i1, int i2, int i3 , int i4, int j1, int j2 , int j3, int j4)
{
    return (board[i1][j1] == board[i2][j2] && board[i2][j2] == board[i3][j3] && board[i3][j3] == board[i4][j4] && board[i1][j1] != ' ');

}

int horizontalCheck()
{
    int row, col;
    for(row =0;row<rows;row++)
    {
      for(col =0;col<(columns-3);col++)
      {
        if(checkFour(row,row,row,row,col,col+1,col+2,col+3))
        {
          return 1;
        }
      }
    }
    return 0;

}

int verticalCheck()
{
    int row, col;
    for(row =0;row<(rows-3);row++)
    {
      for(col =0;col<(columns);col++)
      {
        if(checkFour(row,row+1,row+2,row+3,col,col,col,col))
        {
          return 1;
        }
      }
    }
    return 0;
}

int diagonalCheck()
{
  int row, col ;

for(row = 0; row < (rows-3); row++)
{
   for(col = 0; col < (columns-3); col++)
   {
      if(checkFour(row,row+1,row+2,row+3,col,col+1,col+2,col+3))
      {
         return 1;
      }
   }
}
for(row = 3; row < (rows); row++)
{
   for(col = 0; col < (columns-3); col++)
   {
      if(checkFour(row,row-1,row-2,row-3,col,col+1,col+2,col+3))
      {
         return 1;
      }
   }
}


return 0;

}

void makeBoard()
{
    for(int i=0;i<rows;i++)
    {
      for(int j=0;j<columns;j++)
      {
        board[i][j] = ' ';
      }
    }
}
void printBoard()
{

  for(int i=0;i<rows;i++)
  {
    for(int j=0;j<columns;j++)
    {
      printf("| %c ",board[i][j]);
    }
    puts("|");
    puts("-----------------------------");
    printf("\n");

  }
  puts("  1   2   3   4   5   6   7\n");
}
