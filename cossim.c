#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

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
    //printf("here: ");
    //print_table(table);
    //tranverse the table, check if string is already in there
    while (tmp != table->tail)
    {

        if (strcmp(string, tmp->word) == 0)
        {
            check = true;
            if (whichfile == 1)
            {
                //printf("data1 + 1: %s The word in map is: %s\n", string, tmp->word);
                tmp->data1 += 1;
            }
            else
            {
                //printf("data2 + 1: %s\n", string);
                tmp->data2 += 1;
            }
        }
        tmp = tmp->next;
    }
    if (check == false) //oh it is not in there!!!
    {
        if (whichfile == 1)
        {
            //printf("created new word1: %s\n", string);
            add_to_front(1, 0, string, table);
            //print_table(table);
        }
        else
        {
            //("created new word: %s\n", string);
            add_to_front(0, 1, string, table);
        }
    }
    //printf("In function ");
    //print_table(table);
}

/*double calculator(struct Table *a)
{
    struct Table *table = a;

}*/

///body functions
void reader(struct Table *a) //read and store elements into table
{
    struct Table *table = a;
    char *word1 = malloc(sizeof(char *));

    FILE *fp1 = fopen("result1.txt", "r");
    while (fscanf(fp1, "%s", word1) != EOF)
    {
        printf("%s\n", word1);
        shuffle(word1, 1, table);
        print_table(table);
    }
    fclose(fp1);

    /* FILE *fp2 = fopen("result2.txt", "r");
    while (fscanf(fp2, "%s", word2) != EOF)
    {
        //printf("%s\n", word2);
        shuffle(word2, 2, table);
    }
    fclose(fp2);*/
}

int main()
{
    struct Table *table = create_table();
    char *word1 = malloc(sizeof(char *));

   FILE *fp1 = fopen("result1.txt", "r");

    while (fscanf(fp1, "%s", word1) != EOF)
    {
        //print_table(table);
        printf("%s\n", word1);
        shuffle(word1, 1, table);
        //printf("hey");
        //print_table(table);
    }

    //shuffle("is", 1, table);
    //shuffle("it", 1, table);
    //shuffle("is", 1, table);
    // shuffle("is", 2, table);
    /*add_to_front(1, 0, "hello", table);
    add_to_front(0, 1, "world", table);*/
    print_table(table);
    fclose(fp1);
    return 0;
}
