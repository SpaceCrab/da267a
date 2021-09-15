#include <stdio.h>
#include <limits.h>
#include "circular_buffer.h"



void initCircularBuffer(struct circularBuffer* bufferPtr, int* data, int maxLength, int length) {
    bufferPtr->data = data;
    bufferPtr->head = 0;
    bufferPtr->tail = 0;
    bufferPtr->length = 0;
    bufferPtr->maxLength = maxLength;
}

//Steps through the buffer 
//returns value if the buffer contains value
int contains(struct circularBuffer * bufferPtr, int value)
{
    int *dataPtr = bufferPtr->data;
    int maxLength = bufferPtr->maxLength;
    int head = bufferPtr->head;

    for(int i = 0; i < bufferPtr->length; i++)
    {
        if(dataPtr[head] == value)
        {
            return value;
        }
        else
        {
            head = (head + 1) % maxLength;
        }
    }
    return INT_MIN;
}

// adds Element at tail in the buffer with value value
// if length == maxlength will discard value and return INT_MIN
// returns value if succeeded 
// returns INT_MIN if value discarded
int addElement(struct circularBuffer *bufferPtr, int value)
{
    if(bufferPtr->length == 0)
    {
        bufferPtr->data[bufferPtr->tail] = value;
        bufferPtr->length++;
        return value;
    }
    else if(bufferPtr->length < bufferPtr->maxLength)
    {
        bufferPtr->tail = (bufferPtr->tail +1) % bufferPtr->maxLength;
        bufferPtr->data[bufferPtr->tail] = value;
        bufferPtr->length++;
        return value;
    }
    else
    {
        return INT_MIN;
    }
}

//searches for a value, removes the value 
//shrinks the buffer after removal 
//if value is not found returns INT_MIN
int removeValue(struct circularBuffer *bufferPtr, int value)
{
    int *dataPtr = bufferPtr->data;
    int maxLength = bufferPtr->maxLength;
    int index = bufferPtr->head;
    int tail = bufferPtr->tail;

    for(int i = 0; i < bufferPtr->length; i++)
    {
        if(dataPtr[index] == value)
        {
            do
            {
                bufferPtr->data[index] = bufferPtr->data[(index + 1)%maxLength];
                index = (index +1) % maxLength;
            }while(index != tail);
            
            if(tail == 0)
            {
                bufferPtr->tail = maxLength -1;
            }
            else
            {
                bufferPtr->tail = tail -1;
            }
            return value;
        }
        index = (index +1) % maxLength;
    }

    return INT_MIN;
}

int removeHead(struct circularBuffer *bufferPtr)
{
    int value = bufferPtr->data[bufferPtr->head]; 

    if(bufferPtr->length == 0)
    {
        return INT_MIN;
    }
    else if(bufferPtr->length < bufferPtr->maxLength)
    {
        if(bufferPtr->length > 1)
        {
            bufferPtr->head = (bufferPtr->head +1) % bufferPtr->maxLength;
        }
        bufferPtr->length --;
        return value;
    }

    return INT_MIN;
}

void printBuffer(struct circularBuffer *bufferPtr)
{
    printf("\n");
    for(int i = 0; i < bufferPtr->maxLength; i++)
    {
        printf("|%d",bufferPtr->data[i]);
    }
    printf("\n");
}
