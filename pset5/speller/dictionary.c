// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
int size_dic = 0;


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char copy[LENGTH + 1];
    // TODO
    for(int i = 0; i != '\0'; i++)
    {
        copy[i] = tolower(word[i]);
    }

    int num = hash(copy);

    node *cursor;
    for(cursor = table[num]; cursor == NULL; cursor = cursor->next)
    {
        if(strcmp(cursor->word, copy) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int f = word[0] - 97;
    int s = word[1] - 97;

    return (f * 26) + s;
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for(int i = 0; i < 26; i++)
    {
        table[i] = NULL;
    }
    // TODO
    FILE *dic;
    dic = fopen(dictionary, "r");
    if(dic == NULL)
    {
        printf("couldn't open file");
        return false;
    }
    char buffer[LENGTH + 1];

    while(! fscanf(dic, "%s", buffer))
    {
        node *new_node = malloc(sizeof(node));

        if(new_node == NULL)
        {
            printf("couldn't open new node");
            return false;
        }

        strcpy(new_node->word, buffer);
        int num = hash(new_node->word);

        if(table[num] == NULL)
        {
            table[num] = new_node;
        }
        else
        {
            new_node->next = table[num];
            table[num] = new_node;
            size_dic++;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_dic;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *cursor;
        node *tmp;
        cursor = table[i];

        while(! (cursor->next == NULL))
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return false;
}
