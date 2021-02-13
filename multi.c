// Compile and RUn the Main File.

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
int turn=0;
int score_p1=0;
int score_p2=0;


void bringDown(int row, int col)
{
   for(int i=row;i>0;i--)
   {
     board[i][col] = board[i-1][col];
   }
   if(board[0][col] != ' ')
   {
     board[0][col] = ' ';
   }
}

int takeTurn(int player, const char *PIECES)
{
  display_Align();
  printf("Press 0 to Quit Game\n");
  display_Align();
  printf("Player %d (%c):\n\n\t\t\t\t\t\tEnter number coordinate: ", player + 1, PIECES[player]);
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


        if(col==0)
        {
          if(checkSave())
          {
            saveBoard(player);
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

/*
  Called when Multiplayer is Selected
*/

void onStartMulti()
{
    const char *PIECES = "XO";
    int score_diff =1;
    if(checkDiff()){
      score_diff =2;
    }
    int diff =0;
    if(checkSave()){



      FILE *f;
      f = fopen("saveState.txt", "r");
      if (f)
    	{
    		fseek (f, 0, SEEK_END);
    		int size = ftell(f);
        if(size !=0)
        {
          char chk;  char dumm[1];
            saveinput:
            gets(dumm);
            printf("\t\t\t   Previous Game Save data Found. Do you want to load [y/n].  ");
            scanf("%c",&chk);
            if(chk=='y'){
                LoadBoard();
                printf("\n\n\t\t\t\t  A game with Users: %s and %s is Found!\n\n",current[0].name, current[1].name);
                sleep(2);
            }
            else if(chk=='n')
            {
              select_user();
              makeBoard();
            }
            else
            {
              display_Align();
              printf("Invalid Input. Try again.");
              goto saveinput;
            }
        }
        else
        {
          select_user();
          makeBoard();
        }
    	}
      fclose(f);
      f = fopen("saveState.txt","w");
      fclose(f);
    }
    else
    {
      select_user();
      makeBoard();
    }
    int done=0;
    for(; turn <rows*columns && (diff<score_diff); turn++)
    {
       system("cls");
       display_Align();
       printf("Score Board : P1 : %d :: P2 : %d ::\n\n\n",score_p1,score_p2);
       printBoard();
       while(!takeTurn(turn % 2,PIECES))
       {

          printBoard();
          puts("\n**Column full!**\n");
       }

       label:
       done = checkWin();
       if(done)
       {
         if(win=='X')
         {
           score_p1++;
           win =' ';
         }
         else if(win =='O')
         {
           score_p2++;
           win = ' ';
         }
         diff = abs(score_p1-score_p2);
         if(diff==score_diff)
         {
           break;
         }
       }

       system("cls");
       display_Align();
       printf("Score Board : P1 : %d :: P2 : %d ::\n\n",score_p1,score_p2);
       printBoard();
       if(done)
       {
       goto label;
       }
    }

    system("cls");
    display_Align();
    printf("Score Board : P1 : %d :: P2 : %d ::\n\n",score_p1,score_p2);
    printBoard();

    if(turn == rows*columns && diff!= score_diff)
    {
      display_Align();
      puts("\nIts a Tie");
    }
    else if(diff == score_diff)
    {


      if(score_p1>score_p2)
      {
        display_Align();
        printf("Player 1 (%c) :: %s :: wins !\n", PIECES[0],current[0].name);
        score_p1=0;score_p2=0;
        int index = indexUser(current[0].name);
        users[index].score += 10;
        saveUsers();
      }
      else
      {
        display_Align();
        printf("Player 2 (%c) :: %s ::wins !\n", PIECES[1],current[1].name);
        score_p1=0;score_p2=0;
        int index = indexUser(current[1].name);
        users[index].score += 10;
        saveUsers();
      }
      sleep(3);
      display_play();
    }
}

void select_user()
{
  if(len<2){

    printf("\t\t\tThere are insufficient users, first Add users to play the game...");
    sleep(3);
    display_users();
  }
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
      {
        win = board[row][col];
        if(checkDiff())
        {
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
        if(checkDiff())
        {
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


void saveBoard(int p)
{
  FILE *f;
  f = fopen("saveState.txt","w");
  fputs(current[0].name,f);
  fprintf(f," ");
  fputs(current[1].name,f);
  fprintf(f," ");
  fprintf(f,"%d ",p);
  fprintf(f,"%d ", score_p1 );
  fprintf(f,"%d\n",score_p2 );


  for(int i=0;i<rows;i++)
  {
    for(int j=0;j<columns;j++)
    {
      if(board[i][j]==' '){
        fprintf(f,"-");
      }
      else{
        fprintf(f,"%c",board[i][j]);
      }
    }
  }
    fclose(f);
}

void LoadBoard()
{
  FILE *f;
  f = fopen("saveState.txt","r");
  char dumm[1];
  fscanf(f,"%s %s %d %d %d",current[0].name,current[1].name,&turn,&score_p1,&score_p2);

  char dum;
  fscanf(f,"%c",&dum);
  for(int i=0;i<rows;i++)
  {
    for(int j=0;j<columns;j++)
    {

      fscanf(f,"%c",&board[i][j]);
      if(board[i][j]=='-'){
        board[i][j]= ' ';
      }

    }

  }
  fclose(f);
}

void printBoard()
{

  for(int i=0;i<rows;i++)
  {
    display_Align();
    for(int j=0;j<columns;j++)
    {
      printf("| %c ",board[i][j]);
    }
    puts("|");
    display_Align();
    puts("-----------------------------");
    printf("\n");

  }
  display_Align();
  puts("  1   2   3   4   5   6   7\n");
}
