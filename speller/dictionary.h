/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 46
#define CHARACTERS 27

struct node{
  bool is_word;
  struct node *array[CHARACTERS];
};
typedef struct node node;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Adds a word to the trie structure.
 */
 bool build_trie(char *word);

 /**
  * Returns index of given symbol in trie array a = 0,b = 1... ' = 26.
  */
  int get_index(char symbol);

  /**
   *Creates a new node initializing is_found to false & pointers to NULL.
   */
  node *create_node();

  /**
   *Recursively frees space allocated for node.
   */
   bool return_space(node *target);
#endif // DICTIONARY_H
