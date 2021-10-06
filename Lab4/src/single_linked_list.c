#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

#include"single_linked_list.h"

int addSLL(struct sll* list, int value){
    struct sll_element *element =
        (struct sll_element*)malloc(sizeof(struct sll_element));
    element->next = NULL;
    element->data = value;

    struct sll_element *next;
    struct sll_element *prev;
    
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
        {   element->next = list->first->next;
            list->first = element;
            return value;
        }
        next = list->first;
        prev = list->first;
        element->next = list->first;
        //finds the position to insert element
        //and inserts it
        //if the element is larger than the largest element 
        //insert it at the end
        while(next != NULL)
        {
            //if the element is between 
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
    if(list->first != NULL)
    {
        if(list->first->next != NULL)
        {
            list->first = list->first->next;
            free(list->first->next);
            return list->first->data;
        }
        list->first->data = 0;
        return list->first->data;
    }
    return INT_MIN;
} 

int removeLastSLL(struct sll* list){
    struct sll_element *next = list->first;
    struct sll_element *prev = list->first;

    while(next->next != NULL)
    {
        prev = next;
        next = next->next;
    }

    free(next);
    return prev->data;
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
