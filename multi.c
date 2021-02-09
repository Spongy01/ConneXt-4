/*
  This file contains all the functions
  Required for a multiplayer(1 Vs 1) Gameplay
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "funcs.h"

int rows =6;
int columns =7;
char win =' ';

/*
  Called when Multiplayer is Selected
*/

void bringDown(int row, int col){

   for(int i=row;i>0;i--){
     board[i][col] = board[i-1][col];
   }
   //printBoard();
   //sleep(2);
   if(board[0][col] != ' '){
     board[0][col] = ' ';
   }
}
int takeTurn(int player, const char *PIECES)
{
  printf("Press 0 to Quit Game;");
  printf("Player %d (%c):\nEnter number coordinate: ", player + 1, PIECES[player]);
  int col=0,row=0;
  while(1)
  {
     if(1 != scanf("%d", &col) || col < 0 || col > 7 )
     {
        while(getchar() != '\n');
        puts("Number out of bounds! Try again.");
     }
     else
     {
        if(col==0){
          if(checkSave()){
            saveBoard();
          }
          display_play();
        }
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
    int score_diff =1;
    int score_p1=0;
    int score_p2=0;
    if(checkDiff()){
      score_diff =2;
    }
    int diff =0;
    select_user();
    makeBoard();
    if(checkSave()){
      FILE *f;
      f = fopen("saveState.txt", "r");
      if (f)
    	{
    		fseek (f, 0, SEEK_END);
    		int size = ftell(f);
        if(size !=0)
        {
          LoadBoard();
        }
    	}
      fclose(f);
    }

    int turn=0,done=0;
    for(turn = 0; turn <rows*columns && (diff<score_diff); turn++)
    {
       system("cls");
       printf("Score Board : P1 : %d :: P2 : %d ::\n",score_p1,score_p2);
       printBoard();
       while(!takeTurn(turn % 2,PIECES))
       {

          printBoard();
          puts("\n**Column full!**\n");
       }

       label:

       done = checkWin();
       if(done){
         if(win=='X'){
           score_p1++;
           win =' ';
         }
         else if(win =='O'){
           score_p2++;
           win = ' ';

         }
         diff = abs(score_p1-score_p2);
         if(diff==score_diff){
           break;
         }
       }
       system("cls");
       printf("Score Board : P1 : %d :: P2 : %d ::\n",score_p1,score_p2);
       printBoard();
       if(done){
       goto label;
     }
    }
    system("cls");
    printBoard();

    if(turn == rows*columns && diff!= score_diff)
    {
      puts("\nIts a Tie");
    }
    else if(diff == score_diff)
    {
      if(score_p1>score_p2){
        printf("Player 1 (%c) wins !\n", PIECES[0]);
        int index = indexUser(current[0].name);
        users[index].score += 10;
        saveUsers();
      }
      else{
        printf("Player 2 (%c) wins !\n", PIECES[1]);
        int index = indexUser(current[1].name);
        users[index].score += 10;
        saveUsers();
      }
      sleep(3);
      //char c;
      //printf("Press Enter to Continue>>");
      //getc(c);
      //getc(c);
      display_play();
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
    printf("\n");
    printf("\t\t\tSelect the Player 1:   ");
    gets(nm);
    int check = checkUser(nm);

    if(!check)
    {
      printf("\n\t\t\t\t\tUser Not Found. (Press Enter to Continue)\n");
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
  printf("\n");
  printf("\t\t\tSelect the Player 2:   ");
  gets(nm);
  int check = checkUser(nm);
  if(!check)
  {
    printf("\n\t\t\t\t\tUser Not Found. (Press Enter to Continue)\n");
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
          win = board[row][col];
          if(checkDiff()){

            bringDown(row,col);
            bringDown(row,col+1);
            bringDown(row,col+2);
            bringDown(row,col+3);
          }

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
          win = board[row][col];
          if(checkDiff()){
            bringDown(row+3,col);
            bringDown(row+3,col);
            bringDown(row+3,col);
            bringDown(row+3,col);
          }

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
      {win = board[row][col];
        if(checkDiff()){
          bringDown(row,col);
          bringDown(row+1,col+1);
          bringDown(row+2,col+2);
          bringDown(row+3,col+3);
        }

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
        win = board[row][col];
        if(checkDiff()){
          bringDown(row,col);
          bringDown(row-1,col+1);
          bringDown(row-2,col+2);
          bringDown(row-3,col+3);
        }
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

void saveBoard(){
  FILE *f;
  f = fopen("saveState.txt","w");
  for(int i=0;i<rows;i++)
  {
    for(int j=0;j<columns;j++)
    {
      fprintf(f,"%c",board[i][j]);
    }
  }
    fclose(f);
}
void LoadBoard(){
  FILE *f;
  f = fopen("saveState.txt","r");
  for(int i=0;i<rows;i++)
  {
    for(int j=0;j<columns;j++)
    {
      fscanf(f,"%c",&board[i][j]);
    }
    //fprintf(f, "\n" );
  }
  fclose(f);
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
