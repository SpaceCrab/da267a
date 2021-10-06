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
        while(next != NULL)
        {
            if(prev->data < element->data && next->data > element->data){
                prev->next = element;
                element->next = next;
                return element->data;
            }
            prev = next;
            next = next->next;
        }
        //if the element is larger than the largest element 
        //insert it at the end
        prev->next = element;
        return element->data;
     }

    return INT_MIN;
} 

void initSLL(struct sll* list) {
    list->first = NULL;
}

int removeFirstSLL(struct sll* list){
    return INT_MIN;
} 

int removeLastSLL(struct sll* list){
    return INT_MIN;
} 

void cleanSLL(struct sll* list){
    
}
