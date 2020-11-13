#include <stdio.h>
#include <ctype.h>
#include "cleanup.h"

//to lowercase everything && replace punctuation to ' '
//Harry    last edition:11/10
void cleanup(FILE *fp, FILE *newfp)   /// the thing I think should be perserved in this c file
{
    char ch = getc(fp);
    while (ch != EOF)
    {
        if (ispunct(ch))
        {
            putc(' ', newfp);
        }
        else
        {
            putc(tolower(ch), newfp);
        }
        ch = getc(fp);
    }
}



