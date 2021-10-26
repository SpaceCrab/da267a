#include<stdlib.h>
#include<stdint.h>
#include<limits.h>

#include"double_linked_list.h"

void sortList(struct doubleLinkedList* list){
    struct dllElement *current = list->first;
    struct dllElement *previous = NULL;
    while(current != NULL)
    {
        uint8_t swapped = 0;
        current = list->first;

        while(current != previous && current->next != NULL)
        {
            if(current->data > current->next->data)
            {
                int tmp = current->data;
                current->data = current->next->data;
                current->next->data = tmp;

                swapped = 1;
            }
            current = current->next;
        }
        previous = current;
        if(!swapped)break;
    }
}
int addDLL(struct doubleLinkedList* list, int value){
    struct dllElement *element =
        (struct dllElement*)malloc(sizeof(struct dllElement));
    element->next = NULL;
    element->previous =NULL;
    element->data = value;

    //if the list is empty set first to the added value
    if(list->first == NULL)
    {
        list->first = element;
        list->last = element;
        return element->data;
    }
    else
    {
        element->previous = list->last;
        list->last->next = element;
        list->last = element;
        return element->data;
    }
    return INT_MIN;
} 


void initDLL(struct doubleLinkedList* list) {
  list->first = NULL;
  list->last = NULL;
}


int removeFirstDLL(struct doubleLinkedList* list){
    if(list->first == NULL) return INT_MIN;
    else
    {
        int data = list->first->data;
        struct dllElement *first = list->first;
        if(list->first->next != NULL)
        {
            list->first = list->first->next;
            list->first->previous = NULL;
        }
        free(first);
        return data; 
    }
} 


int removeLastDLL(struct doubleLinkedList* list) {
    if(list->last == NULL) return INT_MIN;
    else
    {
        int data = list->last->data;
        struct dllElement *element = list->last->previous;
        free(list->last);
        list->last = element;
        list->last->next = NULL;
        return data;
    }
    return INT_MIN;
}





