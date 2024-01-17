#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"

int main(){
    HashTable *ht = createTable(CAPACITY);
    add(ht, "1", "First Address");
    add(ht, "2", "Second Address");
    add(ht, "3", "Third Address");
    add(ht, "4", "Fourth Address");
    add(ht, "5", "Fifth Address");
    add(ht, "6", "Sixth Address");
    add(ht, "7", "Seventh Address");
    add(ht, "8", "Eight Address");
    add(ht, "9", "Nine Address"); 
    add(ht, "10", "Ten Address");
    
    printf("Element is: %s \n", get(ht,"1"));
    printf("Element is: %s \n", get(ht,"3"));
    printf("Element is: %s \n", get(ht,"5"));
    printf("Element is: %s \n", get(ht,"7"));
    printf("Element is: %s \n", get(ht,"9"));
    
    displayHashTable(ht);

    printf("After Deleting:\n");
    delete(ht, "7");
    delete(ht, "10");
    delete(ht, "1");
    //deleteItem(ht, "5");

    displayHashTable(ht);
    //printf("Element is: %s \n", getItem(ht,"7"));
    printf("Element is: %s \n", get(ht,"2"));



    return 0;
}




