#include <stdio.h>

char axiomChar = 'X';
int axiomDegree = 90;
char ruleX[] = "XFYFX+F+YFXFY-F-XFYFX";
char ruleY[] = "YFXFY-F-XFYFX+F+YFXFY";
int phase = 1;

int main() {
    printf("Hello World!\n");

    FILE *previousFilePointer;
    FILE *currentFilePointer;
    char charBuffer;

    for(int i = 0; i <= phase; i++) {
        if(i == 0) {
            previousFilePointer = fopen ("previous_file.txt", "w");

            fputc(axiomChar, previousFilePointer);

            fclose (previousFilePointer);

            continue;
        }

        previousFilePointer = fopen("previous_file.txt", "r");
        currentFilePointer = fopen("next_file.txt", "w");

        while ((charBuffer = getc(previousFilePointer)) != EOF) {
            if (charBuffer == 'X') {
                fputs(ruleX, currentFilePointer);
            } else if(charBuffer == 'Y') {
                fputs(ruleY, currentFilePointer);
            } 
            else {
                fputc(charBuffer, currentFilePointer);
            }
        };

        fclose (previousFilePointer);
        fclose (currentFilePointer);

        remove("previous_file.txt");
        rename("next_file.txt", "previous_file.txt");
    }

    previousFilePointer = fopen("previous_file.txt", "r");
    currentFilePointer = fopen("next_file.txt", "w");

    while ((charBuffer = getc(previousFilePointer)) != EOF) {
        if (charBuffer != 'X' && charBuffer != 'Y') {
            fputc(charBuffer, currentFilePointer);
        }
    };

    fclose (previousFilePointer);
    fclose (currentFilePointer);

    remove("previous_file.txt");
    rename("next_file.txt", "previous_file.txt");

    return 0;
}