#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <txlib.h>

#include "doc.h"

int main()
{

    FILE* textcode      = fopen("textcode.txt",      "r"); assert (textcode);
    FILE* numericalcode = fopen("numericalcode.txt", "w"); assert (numericalcode);
    FILE* binarycode    = fopen("binarycode.bin",    "w"); assert (binarycode);

    label labelBuffer [LENOFLABELBUFFER] = {'\0'};

    printf("\n\n****** С ДР, Ванек! *****\n\n\n");

    translator(textcode, numericalcode, binarycode, labelBuffer);

    fclose(textcode);

    return 0;
}



