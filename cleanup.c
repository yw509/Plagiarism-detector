#include <stdio.h>
#include <ctype.h>

//to lowercase everything && replace punctuation to ' '
//Harry    last edition:11/9
void cleanup()
{
    char ch = getchar();
    while (ch != EOF)
    {
        if (ispunct(ch))
        {
            putchar(' ');
        }
        else
        {
            putchar(tolower(ch));
        }
        ch = getchar();
    }
}
