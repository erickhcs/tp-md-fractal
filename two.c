#include <stdio.h>

char axiomChar = 'X';
int axiomDegree = 90;
char ruleX[] = "XFYFX+F+YFXFY-F-XFYFX";
char ruleY[] = "YFXFY-F-XFYFX+F+YFXFY";
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
      previousFilePointer = fopen("result_file_two.txt", "w");

      fputc(axiomChar, previousFilePointer);

      fclose(previousFilePointer);

      continue;
    }

    previousFilePointer = fopen("result_file_two.txt", "r");
    currentFilePointer = fopen("intermediate_file_two.txt", "w");

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

    remove("result_file_two.txt");
    rename("intermediate_file_two.txt", "result_file_two.txt");
  }

  previousFilePointer = fopen("result_file_two.txt", "r");
  currentFilePointer = fopen("intermediate_file_two.txt", "w");

  while ((charBuffer = getc(previousFilePointer)) != EOF)
  {
    if (charBuffer != 'X' && charBuffer != 'Y')
    {
      fputc(charBuffer, currentFilePointer);
    }
  };

  fclose(previousFilePointer);
  fclose(currentFilePointer);

  remove("result_file_two.txt");
  rename("intermediate_file_two.txt", "result_file_two.txt");

  return 0;
}