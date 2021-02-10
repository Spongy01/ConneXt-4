/*
  This file is the Starting point for the Project ConneXt4,
  Connecting other files to itself,
  And calling the Required Functions as needed.
*/
// Importing the necessary Files in Main
#include <stdio.h>
#include <string.h>

#include "display.c"
#include "funcs.h"
/*File Opening, if previously not present, then creation;*/
void init()
{
  FILE *f;
  f = fopen("user.txt","a");
  fclose(f);
  f = fopen("setting.txt", "a");
  if (f)
	{
		fseek (f, 0, SEEK_END);
		int size = ftell(f);
    if(size ==0)
    {
      fprintf(f,"SaveSett 0\nDiff 0\n");
    }
	}
  fclose(f);
  f =fopen("saveState.txt","a");
  fclose(f);

}

int main()
{
  init();
  init_users();
  // Now call the display fuctions to print the game.
  display_credits();
  display_Start();
  return 0;
}
