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
      previousFilePointer = fopen("result_file_one.txt", "w");

      fputc(axiomChar, previousFilePointer);

      fclose(previousFilePointer);

      continue;
    }

    previousFilePointer = fopen("result_file_one.txt", "r");
    currentFilePointer = fopen("intermediate_file_one.txt", "w");

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

    remove("result_file_one.txt");
    rename("intermediate_file_one.txt", "result_file_one.txt");
  }

  return 0;
}