#include <stdio.h>

char axiomChar = 'F';
int axiomDegree = 90;
char rule[] = "F-F+F+FF-F-F+F";
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
      previousFilePointer = fopen("previous_file.txt", "w");

      fputc(axiomChar, previousFilePointer);

      fclose(previousFilePointer);

      continue;
    }

    previousFilePointer = fopen("previous_file.txt", "r");
    currentFilePointer = fopen("next_file.txt", "w");

    while ((charBuffer = getc(previousFilePointer)) != EOF)
    {
      if (charBuffer == 'F')
      {
        fputs(rule, currentFilePointer);
      }
      else
      {
        fputc(charBuffer, currentFilePointer);
      }
    };

    fclose(previousFilePointer);
    fclose(currentFilePointer);

    remove("previous_file.txt");
    rename("next_file.txt", "previous_file.txt");
  }

  return 0;
}