#include <stdio.h>

char axiomChar = 'X';
int axiomDegree = 45;
char ruleX[] = "XFY+F+YFX-F-XFY";
char ruleY[] = "YFX-F-XFY+F+YFX";
int phase = 4;

int main()
{
  FILE *previousFilePointer;
  FILE *currentFilePointer;
  char charBuffer;

  for (int i = 0; i <= phase; i++)
  {
    if (i == 0)
    {
      previousFilePointer = fopen("result_file_three.txt", "w");

      fputc(axiomChar, previousFilePointer);

      fclose(previousFilePointer);

      continue;
    }

    previousFilePointer = fopen("result_file_three.txt", "r");
    currentFilePointer = fopen("intermediate_file_three.txt", "w");

    while ((charBuffer = getc(previousFilePointer)) != EOF)
    {
      if (charBuffer == 'X')
      {
        fputs(ruleX, currentFilePointer);
      }
      else if (charBuffer == 'Y')
      {
        fputs(ruleY, currentFilePointer);
      }
      else
      {
        fputc(charBuffer, currentFilePointer);
      }
    };

    fclose(previousFilePointer);
    fclose(currentFilePointer);

    remove("result_file_three.txt");
    rename("intermediate_file_three.txt", "result_file_three.txt");
  }

  previousFilePointer = fopen("result_file_three.txt", "r");
  currentFilePointer = fopen("intermediate_file_three.txt", "w");

  while ((charBuffer = getc(previousFilePointer)) != EOF)
  {
    if (charBuffer != 'X' && charBuffer != 'Y')
    {
      fputc(charBuffer, currentFilePointer);
    }
  };

  fclose(previousFilePointer);
  fclose(currentFilePointer);

  remove("result_file_three.txt");
  rename("intermediate_file_three.txt", "result_file_three.txt");

  return 0;
}