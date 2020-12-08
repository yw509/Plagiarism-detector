#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LENGTH 30

/*using a trie can be faster to search but I am exhausted */
/* what is the proportion of unimportant word should we cut? */
/* Maybe combine cossim and tfidf later  (faster)*/

struct Node
{
    char *word;
    int count;
    double tf;
    double tf_idf;
    struct Node *next;
};

struct linked_list
{
    int size;
    struct Node *head;
    struct Node *tail;
};

//utility functions for linked_list

struct Node *make_node(int val, char *string, int tfval, struct Node *next)
{
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL)
    {
        return NULL;
    }
    n->count = val;
    n->word = string;
    n->tf = tfval;
    n->tf_idf = 0;
    n->next = next;
    return n;
}

// Create Linked List
struct linked_list *create_ll()
{
    struct linked_list *ll = malloc(sizeof(struct linked_list));
    if (ll == NULL)
    {
        printf("memory allocation failed. \n");
        EXIT_FAILURE;
    }
    ll->head = make_node(-1, "$", 0, NULL);
    ll->tail = make_node(-1, "#", 0, NULL);
    ll->head->next = ll->tail;
    return (ll);
}

struct Node *add_to_beginning(int count, char *string, int tfval, struct linked_list *ll)
{
    struct Node *n = make_node(count, string, tfval, ll->head->next);
    if (ll == NULL)
    {
        printf("memory allocation failed. \n");
        EXIT_FAILURE;
    }
    ll->head->next = n;
    return n;
}

void free_ll(struct linked_list *ll)
{
    struct Node *n = ll->head->next;
    struct Node *tmp;
    while (n != ll->tail)
    {
        tmp = n;
        free(tmp->word);
        free(tmp);
        n = n->next;
    }
    free(ll->head);
    free(ll->tail);
    free(ll);
}

//delete later
void print_ll(struct linked_list *ll)
{
    struct Node *n = ll->head->next;

    while (n != ll->tail)
    {
        printf("%s %d  tfvalue: %f  tfidfvalue: %f\n", n->word, n->count, n->tf, n->tf_idf);
        n = n->next;
    }
}

//delete later
void temp_print(struct linked_list *ll1, struct linked_list *ll2)
{
    struct Node *node1 = ll1->head->next;
    struct Node *node2 = ll2->head->next;
    int size1 = ll1->size * 0.8;
    int size2 = ll2->size * 0.8;

    FILE *fp1 = fopen("result1.txt", "w+");
    while (size1 > 0 && node1 != ll1->tail)
    {

        for (int i = 0; i < node1->count; i++)
        {
            size1--;
            fprintf(fp1, "%s ", node1->word);
        }
        node1 = node1->next;
    }
    fclose(fp1);

    FILE *fp2 = fopen("result2.txt", "w+");
    while (size2 > 0 && node2 != ll2->tail)
    {

        for (int i = 0; i < node2->count; i++)
        {
            size2--;
            fprintf(fp1, "%s ", node2->word);
        }
        node2 = node2->next;
    }
    fclose(fp2);
}

//body functions

int totalword(struct linked_list *ll) ///count total words and store the size
{
    int count = 0;
    struct Node *n = ll->head->next;

    while (n != ll->tail)
    {
        count += n->count;
        n = n->next;
    }
    ll->size = count;
    return count;
}

void calctf(struct linked_list *ll) //calculate the tf of a list of words
{
    int total_word = totalword(ll);
    struct Node *n = ll->head->next;

    while (n != ll->tail)
    {
        n->tf = (double)n->count / total_word;
        n = n->next;
    }
}

void calctfidf(struct linked_list *ll1, struct linked_list *ll2)
{
    bool checker = false;
    struct Node *node1 = ll1->head->next;
    struct Node *node2 = ll2->head->next;

    while (node1 != ll1->tail)
    {
        checker = false;
        char *temp = node1->word;
        while (node2 != ll2->tail)
        {
            if (strcmp(temp, node2->word) == 0)
            {
                checker = true;
                node1->tf_idf = node1->tf * 1; // 1 = 2 / 2
                break;
            }
            node2 = node2->next;
        }
        if (checker == false) //doc2 has no same word
        {
            node1->tf_idf = node1->tf * 2; //2 = 2 / 1
        }
        node1 = node1->next;
    }

    node1 = ll1->head->next;
    node2 = ll2->head->next;
    while (node2 != ll2->tail)
    {
        checker = false;
        char *temp = node2->word;
        while (node1 != ll1->tail)
        {
            if (strcmp(temp, node1->word) == 0)
            {
                checker = true;
                node2->tf_idf = node2->tf * 1; // 1 = 2 / 2
                break;
            }
            node1 = node1->next;
        }
        if (checker == false) //doc1 has no same word
        {
            node2->tf_idf = node2->tf * 2; //2 = 2 / 1
        }
        node2 = node2->next;
    }
}

/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b)
{
    double temp = a->tf_idf; //swap tfidf
    a->tf_idf = b->tf_idf;
    b->tf_idf = temp;

    double temp1 = a->tf; ///swap tf
    a->tf = b->tf;
    b->tf = temp1;

    char *temp2 = a->word; //swap word
    a->word = b->word;
    b->word = temp2;

    int temp3 = a->count; //swap count
    a->count = b->count;
    b->count = temp3;
}

/* Bubble sort the given linked list */
void bubbleSort(struct linked_list *ll)
{
    int swapped;
    struct Node *start = ll->head->next;
    struct Node *ptr1;
    struct Node *lptr = ll->tail;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->tf_idf > ptr1->next->tf_idf)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void distributor(char *word, struct linked_list *ll) //store each word to ll
{

    bool checker = false;
    struct Node *n = ll->head->next;

    while (n != ll->tail)
    {
        if (strcmp(word, n->word) == 0)
        {
            checker = true;
            n->count += 1;
        }
        n = n->next;
    }

    if (checker == false)
    {
        add_to_beginning(1, word, 0, ll);
    }
}

void storager(struct linked_list *ll, char *fname) //read each word to ll
{
    char *word = malloc(sizeof(char) * MAX_LENGTH);

    FILE *fp = fopen(fname, "r");
    while (fscanf(fp, "%s", word) == 1)
    {

        distributor(word, ll);
        word = malloc(sizeof(char) * MAX_LENGTH);
    }
    fclose(fp);
    remove(fname);
}

void tfidf()
{
    struct linked_list *ll1 = create_ll();
    storager(ll1, "result1.txt");
    calctf(ll1);
    //printf("The size is: %d\n", totalword(ll1));
    //print_ll(ll1);

    // printf("\n");

    struct linked_list *ll2 = create_ll();
    storager(ll2, "result2.txt");
    calctf(ll2);
    //printf("The size is: %d\n", totalword(ll2));
    // print_ll(ll2);

    //printf("\n");

    calctfidf(ll1, ll2);
    // print_ll(ll1);
    // printf("\n");
    // print_ll(ll2);

    // printf("\n");
    bubbleSort(ll1);
    //print_ll(ll1);
    //printf("\n");
    bubbleSort(ll2);
    //print_ll(ll2);

    temp_print(ll1, ll2); //delete later
    //free_ll(ll1); //error???
    //free_ll(ll2); //error???
}
