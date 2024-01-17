#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 5

//Entries for Hash Table
typedef struct HashTableEntries{
    char *key;
    char *value;
    struct HashTableEntries *next;    //singly linked list
}HashTableEntries;

//Hashtable
typedef struct HashTable{
    int size;
    HashTableEntries **items; 
}HashTable;

//hash function
unsigned int hashCode(char *key) {
    unsigned long i = 0;
    for (int j=0; j<key[j]; j++)
        i += key[j];
    return i % CAPACITY;
}

//create a new hash table
HashTable *createTable(int size){
    // Creates a new HashTable
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    table->size=size;
    table->items=(HashTableEntries **)calloc(table->size,sizeof(HashTableEntries*));
    return table;
}

//create a new item
HashTableEntries *create_item(char *key, char *value){
    // Creates a pointer to a new hash table item
    HashTableEntries *item = (HashTableEntries *)malloc(sizeof(HashTableEntries));
    item->key = (char *)malloc(strlen(key)+1);
    item->value = (char *)malloc(strlen(value)+1);

    strcpy(item->key,key);
    strcpy(item->value,value);

    item->next = NULL;

    return item;
}
//insert an item
void add(HashTable *table, char *key, char *value){
    
    //compute the slot for the key
    unsigned int index = hashCode(key);    
    //create the item
    HashTableEntries *cur_item = table->items[index];

    //key does not exist,is empty
    if(cur_item == NULL){
        //insert immediately
        table->items[index] = create_item(key,value);
        return;
    }
    HashTableEntries *prev;
    // walk through each entry until either the end is reached or a matching key is found
    while (cur_item != NULL) {
        // check key
        
        if (strcmp(cur_item->key, key) == 0) {
            // replace value when match found
            strcpy(cur_item->value, value);
            return;
        }
        // walk to next
        prev = cur_item;
        cur_item = prev->next;
    }
    // end of chain reached without a match, add new key-value pair
    prev->next = create_item(key, value);
}

//get an item
char *get(HashTable *table, char *key){

    unsigned int index = hashCode(key);
    HashTableEntries *item = table->items[index];
    HashTableEntries *cur = item;

    //loop to get item in case collision occcurs
    while(cur != NULL){
       if(strcmp(cur->key, key) == 0)
           return cur->value;
       cur = cur->next;    
   }
   return NULL;
}

void delete(HashTable *table, char *key) {
    unsigned int bucket = hashCode(key);

    HashTableEntries *item = table->items[bucket];
    
    //list is empty
    if (item == NULL) {
        return;
    }

    HashTableEntries *prev;
    int idx = 0;

    // walk through each entry until either the end is reached or a matching key is found
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            // first item and no next entry
            if (item->next == NULL && idx == 0) {
                table->items[bucket] = NULL;
            }
            // first item with a next entry
            if (item->next != NULL && idx == 0) {
                table->items[bucket] = item->next;
            }
            // last item
            if (item->next == NULL && idx != 0) {
                prev->next = NULL;
            }
            // middle item
            if (item->next != NULL && idx != 0) {
                prev->next = item->next;
            }
            // free the deleted entry
            free(item->key);
            free(item->value);
            free(item);
            return;
        }
        // walk to next
        prev = item;
        item = prev->next;
        ++idx;
    }
}

void displayHashTable(HashTable *table) {
    for (int i = 0; i < CAPACITY; ++i) {
        HashTableEntries *item = table->items[i];

        if (item == NULL) {
            continue;
        }
        

        for(;;) {
            printf("\tslot[%d]:%s-->%s ", i,item->key, item->value);

            if (item->next == NULL) {
                break;
            }

            item = item->next;
        }
        printf("\n");
    }
}




