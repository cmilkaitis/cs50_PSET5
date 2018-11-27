// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Define the structure for linked lists and globals
typedef struct linked_list
{
    char word[LENGTH + 1];
    struct linked_list* next;
}
node;

unsigned int hash_count = 0;
node* hashtable[hashed_words];

unsigned int hash(const char* word)
{
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += word[i];
    }
    return sum % hashed_words;
        // unsigned long hash = 5381;
        // int c = 0;

        // while (c == *str++)
        //     hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        // return hash;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create new word in all lowercase
    int max_length = strlen(word);
    char test[max_length + 1];

    for ( int i = 0; i < max_length; i++ )
    {
       test[i] = tolower(word[i]);
    }

    test[max_length] = '\0';

    // Get the hashtable position of the word to check
    int h = hash(test);
    node* hash_position = hashtable[h];

    // search though the linked list
    while ( hash_position != NULL )
    {
        // if the word is in this list return true
        if ( strcmp(hash_position -> word, test) == 0)
        {
            return true;
        }
        // else move to the next item in the list
        hash_position = hash_position -> next;
    }
    // The word does not exist in the dictionary
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens dictionary file and error checks
    FILE* in = fopen(dictionary, "r");

    if ( in == NULL )
    {
        printf("File could not open.\n");
        return 1;
    }

    // Set word to LENGTH as defined in dic.h plus 1 for '\0'
    char word[LENGTH + 1];

    // loop over each word via file formart until you reach End Of File
    while ( fscanf(in, "%s\n", word) != EOF )
    {

        node* new_node = malloc(sizeof(node));
        new_node -> next = NULL;

        if (new_node == NULL)
        {
            printf("No memory available");
            return false;
        }

        unsigned int hash_position = hash(word);
        node* head = hashtable[hash_position];
       // new_node -> word = malloc(sizeof(word) + 1);
        strcpy(new_node -> word, word);

        if (head == NULL)
        {
            hashtable[hash_position] = new_node;
        }

        new_node -> next = hashtable[hash_position];
        hashtable[hash_position] = new_node;

        hash_count++;

    }
    fclose(in);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return hash_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < hashed_words; i++)
    {
        free(hashtable[i]);
    }
    return true;
}
