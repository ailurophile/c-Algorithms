/**
 * Implements a dictionary's functionality.
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

//root of Trie
node *root;
int word_count = 0;
/**
 *Creates a new node initializing is_found to false & pointers to NULL.
 */
node *create_node()
{
  node *new_node = malloc(sizeof(node));
  if (new_node != NULL){
    new_node->is_word = false;
    memset(new_node->array, 0, sizeof(new_node->array));
  }
  return new_node;
}
/**
 * Returns index of given symbol in trie array a = 0,b = 1... ' = 26.
 */
 int get_index(char symbol)
 {
   if (symbol == '\'')
   {
     return 26;
   }
   return symbol - 'a';
 }
/**
 * Adds a word to the trie structure.
 */
bool build_trie(char *word)
 {
   char *ptr = word;
   char symbol = *ptr++;
   node *trie = root;
   while( (symbol != '\n') && (symbol != '\0') )
   {
     int index = get_index(symbol);
     if (trie->array[index] == NULL)
     {
       trie->array[index] = create_node();
       if (trie->array[index] == NULL)
       {
           return false;
       }
     }
     //advance to next character in word
     trie = trie->array[index];
     symbol = *ptr++;
   }
   // at end of word so set is_word to true
   trie->is_word = true;
   return true;
 }
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
  char *ptr = (char *)word;
  node *trie = root;
  char letter = tolower(*ptr++);
  while ( (letter != '\n') && (letter != '\0'))
  {
    int index = get_index(letter);
    if (trie->array[index] == NULL)
    {
      return false;
    }
    //advance to next character in word
    trie = trie->array[index];
    letter = tolower(*ptr++);

  }
  return trie->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
  root = create_node();
  if (root == NULL)
  {
    fprintf(stderr, "Could not allocate node");
    return false;
  }
  // Open dictinary file
  FILE *file = fopen(dictionary, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Could not open dictionary");
    return false;
  }
  // Read words until end of file
  char word[LENGTH + 2];
  while( fgets( word, LENGTH+1, file) != NULL)
  {

    if (!build_trie(word))
    {
        return false;
    }
    word_count += 1;

  }
  fclose(file);

  return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    return word_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{

    return return_space(root);
}
/**
 *Recursively frees space allocated for node.
 */
 bool return_space(node *target)
 {
   for (int i = 0; i < CHARACTERS; i++)
   {
     if (target->array[i] != NULL)
     {
       return_space(target->array[i]);
     }
   }
   free(target);
   return true;

 }
