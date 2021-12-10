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

    translator(textcode, numericalcode, binarycode);

    fclose(textcode);

    return 0;
}



