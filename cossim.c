#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "cossim.h"
#include <limits.h>
#define MAX_LENGTH 30
#define FILE_MAX 102400
//structure
struct Node
{
    char *word;
    int data1;
    int data2;
    struct Node *next;
};

struct Table
{
    struct Node *head;
    struct Node *tail;
};

///utility functions
struct Node *create_node(int count1, int count2, char *string, struct Node *next)
{
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL)
    {
        printf("memory allocation failed. \n");
        EXIT_FAILURE;
    }
    n->data1 = count1;
    n->data2 = count2;
    n->word = string;
    n->next = next;
    return n;
}

struct Table *create_table()
{
    struct Table *new = malloc(sizeof(struct Table));
    if (new == NULL)
    {
        printf("memory allocation failed. \n");
        EXIT_FAILURE;
    }
    new->head = create_node(-1, -1, "$", NULL);
    new->tail = create_node(-1, -1, "$", NULL);
    new->head->next = new->tail;
    return new;
}

struct Node *add_to_front(int count1, int count2, char *string, struct Table *table)
{
    struct Node *n = create_node(count1, count2, string, table->head->next);
    if (n == NULL)
    {
        return NULL;
    }
    table->head->next = n;
    return n;
}

void lucky_free(struct Table *table)
{
    struct Node *n = table->head->next;
    struct Node *tmp;
    while (n != table->tail)
    {
        tmp = n;
        n = n->next;
        //free(tmp->word);
        free(tmp);
    }
    free(table->head);
    free(table->tail);
    free(table);
}

//delete later
void print_table(struct Table *table)
{
    struct Node *n = table->head->next;
    while (n != table->tail)
    {
        printf("%s %d %d\n", n->word, n->data1, n->data2);
        n = n->next;
    }
}

void shuffle(char *string, int whichfile, struct Table *a)
{
    bool check = false;
    struct Table *table = a;
    struct Node *tmp = table->head->next;

    //tranverse the table, check if string is already in there
    while (tmp != table->tail)
    {

        if (strcmp(string, tmp->word) == 0)
        {
            check = true;
            if (whichfile == 1)
            {
                tmp->data1 += 1;
            }
            else
            {
                tmp->data2 += 1;
            }
        }
        tmp = tmp->next;
    }
    if (check == false) //oh it is not in there!!!
    {
        if (whichfile == 1)
        {
            add_to_front(1, 0, string, table);
        }
        else
        {
            add_to_front(0, 1, string, table);
        }
    }
    
}

double calculator(struct Table *a)
{
    struct Table *table = a;
    struct Node *tmp = table->head->next;
    int numerator = 0, collector1 = 0, collector2 = 0;
    double denominator, result;

    while (tmp != table->tail)
    {
        numerator += tmp->data1 * tmp->data2;
        collector1 += tmp->data1 * tmp->data1;
        collector2 += tmp->data2 * tmp->data2;
        tmp = tmp->next;
    }
    denominator = sqrt(collector1) * sqrt(collector2);

    result = numerator / denominator;
    result = result * 100;
    return result;
}


//main function of this file
void cossim()
{
    struct Table *table = create_table();
    char *word1[FILE_MAX];
    char str1[FILE_MAX];
    char *word2[FILE_MAX];
    char str2[FILE_MAX];
    int n1=0;
    int n2=0;
    FILE *fp1 = fopen("result1.txt", "r");
    while (fscanf(fp1, "%s", str1) != EOF)
    {
        word1[n1]=malloc(sizeof(char) * MAX_LENGTH);
        strcpy(word1[n1],str1);
        shuffle(word1[n1], 1, table);
        n1++;
    }
    fclose(fp1);

    FILE *fp2 = fopen("result2.txt", "r");
    while (fscanf(fp2, "%s", str2) != EOF)
    {
        word2[n2]=malloc(sizeof(char) * MAX_LENGTH);
        strcpy(word1[n2],str2);
        shuffle(word1[n2], 2, table);
        n2++;
    }
    fclose(fp2);
    printf("The cosine similarity is: %.2f%%\n", calculator(table));
    for (int i = 0; i < n1; i++) {
      free(word1[i]);
    }
    for (int i = 0; i < n2; i++) {
      free(word2[i]);
    }
    lucky_free(table);
}

