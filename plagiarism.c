#include <stdio.h>
#include "cleanup.c"

int main(int argc, char *argv[]) //the thing I think should NOT be perserved in this c file. It should be showed in plagiarlism.c
{
    int index = 0;
    FILE *fp, *newfp;
    char *names[100] = {"result1.txt", "result2.txt", "result3.txt"};
    for (int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
        fp = fopen(argv[i], "r");
        newfp = fopen(names[index], "a");
        cleanup(fp, newfp);
        fclose(fp);
        fclose(newfp);
        index++;
    }

    return 0;
}