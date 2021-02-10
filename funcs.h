#ifndef FUNCS_H
#define FUNCS_H

struct data{char name[20];int score;}users[10];
struct sett{char setting[20];int value;}settings[2];
struct user{char name[20];}current[2];
int len=0;
  char board[6][7];

void extractUsers();
int countUsers();
void saveUsers();
void printUsers();
int AddUser(char m[]);
int DelUser(char nm[]);
int indexUser(char nm[]);

void loadSettings();
void saveSettings();
int checkSave();
void ammendSave(int n);
int checkDiff();
void ammendDiff(int n);

void display_Align();
void display_Start();
void display_play();
void display_users();
void display_options();
void display_exit();
void display_setting();
void display_savestate();
void display_modes();
void display_credits();

void saveBoard(int);
void LoadBoard();
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
#endif
