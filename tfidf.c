#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tfidf.h"
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
    double result = (2.0 / ((double)countt+1));
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
        fclose(fp);
    }
    lengths[0] = index;
    lengths[1] = index2;
    return lengths;
}

///reads single file and store words to array. return length of arr
int readinput(char *filename, char **words)
{
    int wordsindex = 0;
    char *word = malloc(MAXLENGTH);
    FILE *fp = fopen(filename, "r");
    while (fscanf(fp, "%s", word) != EOF)
    {
        words[wordsindex] = malloc(strlen(word) + 1);
        strcpy(words[wordsindex], word);
        wordsindex++;
    }
    fclose(fp);
    return wordsindex;
}
int int_cmp(const void *a, const void *b)
{
    char *resta, *restb;

    char *ia = *(char **)a;
    char *ib = *(char **)b;
    long numbera = strtol(ia, &resta, 10);
    long numberb = strtol(ib, &restb, 10);
    if ((numbera - numberb) > 0)
    {
        return 1;
    }
    else if ((numbera - numberb) < 0)
    {
        return -1;
    }
    else
    {
        return strcmp(resta, restb);
    }
}

void replaceword(char *fname, char *word)
{
    char *w=word;
    FILE *fp1, *fp2;
    char string[MAXLENGTH], replace[] = " ";
    char temp[] = "temp.txt";

    /* open input file in read mode */
    fp1 = fopen(fname, "r");

    /* open temporary file in write mode */
    fp2 = fopen(temp, "w");

    while (fscanf(fp1, "%s", string) != EOF)
    {
        if (strcmp(string, w) == 0)
        {
            fputs(replace, fp2);
        }
        else
        {
            fputs(string, fp2);
            fputs(" ", fp2);
        }
    }

    /* close the opened files */
    fclose(fp1);
    fclose(fp2);

    /* remove the input file */
    remove(fname);
    /* rename temporary file name to input file name */
    rename(temp, fname);
}

void digit_sort(char **lines, size_t length, char **removewords, char *fname)
{   char **rw=removewords;
    int index=0;
    char *rest;
    qsort(lines, length, sizeof(char *), int_cmp);
    long first = strtol(lines[0], &rest, 10);

    for (int i = 0; i < (int)length; i++)
    {
        long tfidf = strtol(lines[i], &rest, 10);
        //printf("%ld\n", strtol(lines[i], &rest, 10)); 
         //printf("%s\n", rest);
        if (tfidf < (first + 500))  ///important ! set the flow
        {
            rw[index] = malloc(strlen(rest) + 1);
            strcpy(rw[index], rest);
            index++;
        }
    }
    for (int r = 0; r < index; r++)
    {
        replaceword(fname, rw[r]);
	free(rw[r]);
    }
}

void tfidf(char **fnames)
{
    ///read()
    int *filelengths, filelength1, filelength2;
    char **file1words = malloc(sizeof(char *) * MAXLENGTH * MAXLENGTH);
    char **file2words = malloc(sizeof(char *) * MAXLENGTH * MAXLENGTH);
    filelengths = reader(fnames, 2, file1words, file2words); ///set number of file to 2
    filelength1 = filelengths[0];
    filelength2 = filelengths[1];

    //store()
    //store file1
    char **storedfile1words = malloc(sizeof(char *) * (filelength1 - 1) * MAXLENGTH);
    int storedfile1num[filelength1 - 1];
    int file1count = storager(file1words, filelength1, storedfile1words, storedfile1num);
    //store file2
    char **storedfile2words = malloc(sizeof(char *) * (filelength2 - 1) * MAXLENGTH);
    int storedfile2num[filelength2 - 1];
    int file2count = storager(file2words, filelength2, storedfile2words, storedfile2num);

    ///turn double into string, give a list of int+word
    //file1
    char **file1 = malloc(MAXLENGTH * MAXLENGTH);
    char **removewords1 = malloc(MAXLENGTH * MAXLENGTH);
    char tfidf1[file1count];
    char **tfidffile1 = malloc(MAXLENGTH * MAXLENGTH);
    int originallength1 = readinput("result1.txt", file1);
    for (int z = 0; z < originallength1; z++)
    {
        sprintf(tfidf1, "%d", (int)(tf(storedfile1words, file1[z], storedfile1num, filelength1, file1count) * idf(storedfile1words, storedfile2words, file1[z], file1count, file2count) * 1000000));
        strcat(tfidf1, file1[z]);
        tfidffile1[z] = malloc(strlen(tfidf1) + 1);
        strcpy(tfidffile1[z], tfidf1);
    }
    digit_sort(tfidffile1, originallength1, removewords1, "result1.txt");
    //file2
    char **file2 = malloc(MAXLENGTH * MAXLENGTH);
    char **removewords2 = malloc(MAXLENGTH * MAXLENGTH);
    char tfidf2[file2count];
    char **tfidffile2 = malloc(MAXLENGTH * MAXLENGTH);
    int originallength2 = readinput("result2.txt", file2);
    for (int z = 0; z < originallength2; z++)
    {
        sprintf(tfidf2, "%d", (int)(tf(storedfile2words, file2[z], storedfile2num, filelength2, file2count) * idf(storedfile2words, storedfile1words, file2[z], file2count, file1count) * 1000000));
        strcat(tfidf2, file2[z]);
        tfidffile2[z] = malloc(strlen(tfidf2) + 1);
        strcpy(tfidffile2[z], tfidf2);
    }
    digit_sort(tfidffile2, originallength2, removewords2, "result2.txt");
    free(file1words);
    free(file2words);
    free(storedfile1words);
    free(storedfile2words);
    free(removewords1);
    free(tfidffile1);
    free(file1);
    free(file2);
    free(removewords2);
    free(tfidffile2);

}
