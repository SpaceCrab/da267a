#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include"single_linked_list.h"

int addSLL(struct sll* list, int value){
    struct sll_element *element =
        (struct sll_element*)malloc(sizeof(struct sll_element));
    element->next = NULL;
    element->data = value;

    struct sll_element *next = list->first;;
    struct sll_element *prev = list->first;;
    
    //if the list is empty set first to the added element
    if(list->first == NULL )
    {
        list->first = element;
        return element->data;
    }
    else
    {
        //checks if element should be inserted into the first position
        if(list->first->data > value)
        {
            element->next = list->first->next;
            list->first = element;
            return value;
        }

        //finds the position to insert element
        //and inserts it
        //if the element is larger than the largest element 
        //insert it at the end
        while(next != NULL)
        {
            //if the element fits between prev and next
            if(prev->data <= element->data && next->data > element->data){
                prev->next = element;
                element->next = next;
                return element->data;
            }
            prev = next;
            next = next->next;
        }
        prev->next = element;
        return element->data;
     }

    return INT_MIN;
} 

void initSLL(struct sll* list) {
    list->first = NULL;
}

int removeFirstSLL(struct sll* list){
    if(list->first == NULL) return INT_MIN;
    int data = list->first->data;
    struct sll_element *element = list->first->next;
    free(list->first);
    list->first = element;
    return data;
} 

int removeLastSLL(struct sll* list){
    if(list->first == NULL) return INT_MIN;

    struct sll_element *next = list->first;
    struct sll_element *prev = list->first;

    while(next->next != NULL)
    {
        prev = next;
        next = next->next;
    }
    if(next == list->first) list->first = NULL;
    if(prev != NULL) prev->next = NULL;
    free(next);
    return list->first->data;
} 

void cleanSLL(struct sll* list){
    struct sll_element *next = list->first;
    struct sll_element *prev = list->first;
    while(next != NULL)
    {
        prev = next;
        next = next->next;
        free(prev);
    }
}
