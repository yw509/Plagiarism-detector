#include <stdio.h>
#include "cleanup.h"
#include "tfidf.h"
#include "cossim.h"
#include <stdlib.h>

int main(int argc, char *argv[]) //the thing I think should NOT be perserved in this c file. It should be showed in plagiarlism.c
{
    int index = 0;
    FILE *fp, *newfp;
    char *names[100] = {"result1.txt", "result2.txt"};
    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("File not exists: %s\n", argv[i]);
            exit(1);
        }
        newfp = fopen(names[index], "w");
        cleanup(fp, newfp);
        fclose(fp);
        fclose(newfp);
        index++;
    }

    //tfidf(names);
    cossim();
    remove("result1.txt");
    remove("result2.txt");
    return 0;
}
