#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"



List* init_history(){
  List *list = (List *)malloc(sizeof(List));
  if (list != NULL){
    list->root = NULL;
    list->size = 0;//for id
}
  return list;
}

void add_history(List *list, char *str) {
    if (list == NULL || str == NULL) {
        return; 
    }
    //making memory, will return if doesn't work 
    Item *new_item = (Item *)malloc(sizeof(Item));
    if (new_item == NULL) {
        return; 
    }
    
    new_item->str = (char *)malloc(strlen(str) + 1);//used string.h,
    if (new_item->str == NULL){ 
        free(new_item); 
        return;
    }
    strcpy(new_item->str, str); // used string.h

    new_item->id = list -> size;
    new_item->next = NULL; 

    // empty list append, else loop for non empty list append
    if (list->root == NULL) {
        list->root = new_item;
    } else {
        Item *current = list->root;
        while (current->next != NULL) {
	  current = current->next; //while goes to last node, 
        }
        current->next = new_item; //, this puts new item in last node
    }
    list->size++;
}
// returns string at given id
char *get_history(List *list, int id) {
    if (list == NULL || id < 0 || id >= list->size) {
        return NULL; // make sure valid parameters
    }

    Item *current = list->root;
    while (current != NULL) {
        if (current->id == id) {
            return current->str; // if id matches return the string in the item
        }
        current = current->next; 
    }

    return NULL; // NULL if can't find matching id
}


void print_history(List *list) {
    if (list == NULL) {
        printf("empty list");
        return;
    }

    Item *current = list->root;//set new item to root
    while (current != NULL) {
        printf("ID: %d, String: %s\n", current->id, current->str);
        current = current->next;
    }
}

void free_history(List *list) {
    if (list == NULL) {
        return;
    }

    Item *current = list->root;
    while (current != NULL) {
        Item *to_free = current; //to_free is temp  
        current = current->next;  
        free(to_free->str);       // free the string and item  memory
        free(to_free);           
    }
    free(list); // free the list
}

