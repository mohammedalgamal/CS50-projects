// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500;//5381;//676;

//word count
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    //hash word
    unsigned int idx = hash(word);

    //access linked list at idx
    node *l_list = table[idx];

    if (l_list == NULL)
    {
        return false;
    }

    //traverse
    while (l_list != NULL)
    {
        if (strcasecmp(l_list->word, word) == 0)
        {
            return true;
        }
        l_list = l_list->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    /*if (strlen(word) > 2)
    {
        int ff = (toupper(word[0]) - 'A');
        int ss = (toupper(word[1]) - 'A');
        int th = (toupper(word[2]) - 'A');
        int tt = (ff * 26) + (ss * 676) + th;
        return tt;
    }*/
    /*if (strlen(word) > 1)
    {
        int f = (toupper(word[0]) - 'A');
        int s = (toupper(word[1]) - 'A');
        int t = (f * 26) + s;
        return t;
    }
    return toupper(word[0]) - 'A';*/
    /*int tt = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if ((toupper(word[i]) - 'A') >= 0)
        {
            tt += (toupper(word[i]) - 'A');
        }
    }
    return tt;*/
    /*unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c;  hash * 33 + c
    }
    return hash % N;*/
    unsigned int value = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        value = value + 37 * tolower(word[i]);
    }
    value = value % N;
    return value;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dict
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //Read strings
    char *buffer = malloc(LENGTH);

    while (fscanf(file, "%s", buffer) != EOF)
    {
        //create new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }
        strcpy(n->word, buffer);

        //hash word
        unsigned int idx = hash(n->word);

        //insert node
        n->next = table[idx];
        table[idx] = n;

        //inc count
        count++;
        //free(n);
    }
    free(buffer);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *l_list = table[i];
        while (l_list != NULL)
        {
            node *tmp = l_list->next;
            free(l_list);
            l_list = tmp;
        }
        if (i == N - 1 && l_list == NULL)
        {
            return true;
        }
    }
    return false;
}
