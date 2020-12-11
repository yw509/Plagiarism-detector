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

    if (argc == 1)
    {
        printf("Please enter two input files.\n");
        exit(1);
    }

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

    tfidf();

    FILE *fp1, *fp2;
    fp1 = fopen("result1.txt", "r");
    fseek(fp1, 0, SEEK_END);
    int size1 = ftell(fp1);
    fp2 = fopen("result2.txt", "r");
    fseek(fp2, 0, SEEK_END);
    int size2 = ftell(fp2);
    fclose(fp1);
    fclose(fp2);

    if (0 == size1 && 0 == size2)
    {
        printf("The similarity between these two files is: 100.00%%\n");
    }
    else
    {
        cossim();
    }

    remove("result1.txt");
    remove("result2.txt");
    return 0;
}
