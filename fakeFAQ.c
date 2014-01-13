#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getresp(char * answer, int size )
{
  int i;
  char letter;
  struct termios stModifiedTerm;
  struct termios stOriginalTerm;
  char * question = malloc((char)100*sizeof(char));
  question = "Qual e o seu nome";

  tcgetattr(0, &stModifiedTerm);
  stOriginalTerm = stModifiedTerm;

  /* Does NOT echo the char typed on screen */
  stModifiedTerm.c_lflag&=~(ECHO|ICANON);
  stModifiedTerm.c_cc[VMIN]=1;
  stModifiedTerm.c_cc[VTIME]=0;
  tcsetattr(0, TCSAFLUSH, &stModifiedTerm);

  for( i=0; i< size -1; i++)
  {
    letter=getchar();
    if ((letter == '\b') || (letter == '\n') || (letter == ';'))
      break;
    answer[i]=letter;
    char c = question[i];
    fprintf(stderr, &c);
  }
  answer[i] = '\0';

  /* Restore term settings */
  tcsetattr(0, TCSAFLUSH, &stOriginalTerm);
  return;
}

int main(void)
{
   char answer[30];
   char question[90];
   memset(question,0, sizeof(question));
   memset(answer,0, sizeof(answer));
   system("clear");
   printf("\nP:");
   getresp(answer,30);
   scanf("%s",question);
   printf("\nR: %s\n", answer);
   return 0;
}
