#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#define MAXLENGTH 1024

///two docs
///store word and its occurence in words and num accordingly. return number of elements in words
int storager(char **arr, int length, char **words, int num[])
{
    int index = 0, contain = 1, count = 0; //contain = 1 represents arr[index] is not in words

    for (int i = 0; i < length; i++)
    {
        for (index = 0; index < count; index++)
        {
            if (strcmp(arr[i], words[index]) == 0)
            {
                num[index] += 1;
                contain = 0;
                break;
            }
            else
            {
                contain = 1;
            }
        }

        if (contain == 1)
        {
            words[count] = malloc(strlen(arr[i]) + 1);
            strcpy(words[count], arr[i]);
            count += 1;
            num[index] = 1;
        }
        contain = 1;
    }

    return count;
}

///return the tf of word target
double tf(char **words, char *target, int num[], int length, int count)
{
    int countt;
    double tf;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(words[i], target) == 0)
        {
            countt = num[i];
            break;
        }
    }
    tf = (double)countt / (double)length;
    return tf;
}

double idf(char **storedfile1words, char **storedfile2words, char *target, int file1count, int file2count)
{
    int countt = 0;
    double idf;
    for (int i = 0; i < file1count; i++)
    {
        if (strcmp(storedfile1words[i], target) == 0)
        {
            countt++;
            break;
        }
    }

    for (int q = 0; q < file2count; q++)
    {
        if (strcmp(storedfile2words[q], target) == 0)
        {
            countt++;
            break;
        }
    }
    double result = (2.0 / (double)countt);
    //printf("%lf\n", result);
    idf = log(result) / log(10);
    return idf;
}
///PROBLEM!!!    Only can read two files
//store lists of words of two files, return array contains two lengths
int *reader(char **fname, int numfile, char **words, char **words2)
{
    int index = 0, index2 = 0;
    static int lengths[2];
    char *word = malloc(sizeof(char) * MAXLENGTH);
    char *word2 = malloc(sizeof(char) * MAXLENGTH);

    for (int i = 0; i < numfile; i++)
    {
        FILE *fp = fopen(fname[i], "r");
        if (i == 1)
        {
            while (fscanf(fp, "%s", word2) != EOF)
            {
                words2[index2] = malloc(strlen(word2) + 1);
                strcpy(words2[index2], word2);
                index2++;
            }
        }
        else
        {
            while (fscanf(fp, "%s", word) != EOF)
            {
                words[index] = malloc(strlen(word) + 1);
                strcpy(words[index], word);
                index++;
            }
        }
    }
    lengths[0] = index;
    lengths[1] = index2;
    return lengths;
}

int main()
{
    ///read()
    int *filelengths, filelength1, filelength2;
    char *fname[2] = {"result1.txt", "result2.txt"};
    char **file1words = malloc(sizeof(char *) * MAXLENGTH * MAXLENGTH);
    char **file2words = malloc(sizeof(char *) * MAXLENGTH * MAXLENGTH);
    filelengths = reader(fname, 2, file1words, file2words);
    filelength1 = filelengths[0];
    filelength2 = filelengths[1];
    for (int q = 0; q < filelength1; q++)
    {
        printf("%s\n", file1words[q]);
    }
    for (int k = 0; k < filelength2; k++)
    {
        printf("%s\n", file2words[k]);
    }
    printf("%d\n", filelength1);
    printf("%d\n", filelength2);

    //store file1
    char **storedfile1words = malloc(sizeof(char *) * (filelength1 - 1) * MAXLENGTH);
    int storedfile1num[filelength1 - 1];
    int file1count = storager(file1words, filelength1, storedfile1words, storedfile1num);
    printf("file1count: %d\n", file1count);

    //store file2
    char **storedfile2words = malloc(sizeof(char *) * (filelength2 - 1) * MAXLENGTH);
    int storedfile2num[filelength2 - 1];
    int file2count = storager(file2words, filelength2, storedfile2words, storedfile2num);
    printf("file2count: %d\n", file2count);

    //tf of i in file1 and file2
    printf("%lf\n", tf(storedfile1words, "i", storedfile1num, filelength1, file1count));
    printf("%lf\n", tf(storedfile2words, "i", storedfile2num, filelength2, file2count));

    //idf
    //printf("%lf\n", idf(storedfile1words, storedfile2words, "zhang", file1count, file2count));

    //finally! single word
    printf("%lf\n", (tf(storedfile1words, "weirdo", storedfile1num, filelength1, file1count) * idf(storedfile1words, storedfile2words, "weirdo", file1count, file2count)));
    printf("%lf\n", (tf(storedfile1words, "i", storedfile1num, filelength1, file1count) * idf(storedfile1words, storedfile2words, "i", file1count, file2count)));

    return 0;
}
