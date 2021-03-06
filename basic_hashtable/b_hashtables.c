#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function
  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;  // cast the input str from a char * to an unsigned char * called u_str

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/****
  Fill this in.
  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));   // allocate memory for a BasicHashTable struct type as defined above and return a pointer to it
  ht->capacity = capacity;
  ht->storage = calloc(capacity, sizeof(Pair));  // ??? Should this use sizeof(Pair) or sizeof(Pair *) ???
  return ht;
}

/****
  Fill this in.
  If you are overwriting a value with a different key, print a warning.
  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  unsigned int hashed_key = hash(key, ht->capacity);
  Pair *pair = create_pair(key, value); // I'm not sure if the key here should be hashed or not
  if (ht->storage[hashed_key] != NULL) {
    printf("Warning: You are overwriting an existing value in the hash table.");
    destroy_pair(ht->storage[hashed_key]);
  }
  ht->storage[hashed_key] = pair;
}

/****
  Fill this in.
  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  unsigned int hashed_key = hash(key, ht->capacity);
  if (ht->storage[hashed_key] != NULL) { // if the hashed key is in the table
    destroy_pair(ht->storage[hashed_key]);
    ht->storage[hashed_key] = NULL;
  } else {
    printf("No pair with that key was found in the hash table.");
    return;
  }
}

/****
  Fill this in.
  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  unsigned int hashed_key = hash(key, ht->capacity);
  if (ht->storage[hashed_key] != NULL) {     // if the hashed key is in the table. ? do I need to check if ht->storage[hashed]->key is actually equal to input key
    return ht->storage[hashed_key]->value;
  } else {
    printf("No pair with that key was found in the hash table.");
    return NULL;
  }
}

/****
  Fill this in.
  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  // for-loop through the hash table and run destroy_pair on each non-null pair:
  for (int i = 0; i < ht->capacity; i++) {
    if (ht->storage[i] != NULL) {
      destroy_pair(ht->storage[i]);
    }
  }
  // free the relevant memory:
  free(ht->storage);
  free(ht);
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
