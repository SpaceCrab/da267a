#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <esp32/rom/ets_sys.h>
#include "circular_buffer.h"

#define TEST_ASSERT(test, ...) do { \
    printf(__VA_ARGS__);            \
    if (!(test)) {                  \
        printf("Aseertion Failed: (%s), func %s, file %s, line %d\n", #test, __FUNCTION__, __FILE__, __LINE__); \
    } else { printf("\tPassed\n"); }} while(0)
#define TEST_RUN(test) do { printf("TEST: %s\n", #test); test(); } while(0)
/*
 * Change the value of BUFFER_SIZE if you want to change the size of the buffer. 
 */ 
#define BUFFER_SIZE 4

//Adds an element to the buffer and then removes the element
//test succeeds if the removed element is the same as the added element
void testAddRemove()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    int added = addElement(&buffer, 3);
    int removed = removeHead(&buffer);

    TEST_ASSERT(added == removed, "test \tadd element %d\n \tremoved %d\n", added, removed);

    printBuffer(&buffer);
    free(buffer_data);

}

//adds 2 elements and then removes 2 elements
//test succeeds if the two added elements are the same as the added elements 
//and in the same order
void testAddRemove2()
{
   struct circularBuffer buffer;
   int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
   initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
   int valAdd1 = 1;
   int valAdd2 = 2;

   addElement(&buffer, valAdd1);
   addElement(&buffer, valAdd2);
   int valRem1 = removeHead(&buffer);
   int valRem2 = removeHead(&buffer);

   TEST_ASSERT(valAdd1 == valRem1&&valAdd2 == valRem2,
           "test \t add element %d \n\t removed %d \n\t test \n\t add element %d \n\t removed %d\n\t", 
           valAdd1, valRem1, valAdd2, valRem2);
    printBuffer(&buffer);
    free(buffer_data);
}

//fills the buffer with data and then removes the data
//test succeeds if the added data is the same and in the same order as the added data
void testAddRemoveFull()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    int temp;
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        addElement(&buffer, i);
    }
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        temp = removeHead(&buffer);
        TEST_ASSERT(i == temp, "test \t add element %d \n\t removed %d\n\t",
                i, temp );
    }
    printBuffer(&buffer);
    free(buffer_data);
}

//attempts to add BUFFER_SIZE +1 elements to the buffer
//test succeds if the last element added is discarded
void testAddDiscardOnFull()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    int temp;
    for(int i = 0; i < BUFFER_SIZE +1; i++)
    {
        addElement(&buffer, i);
    }
    temp = removeHead(&buffer);
    TEST_ASSERT(temp != BUFFER_SIZE, "test \t removed %d \n\t buffer size %d\n\t", 
            temp, BUFFER_SIZE);
    printBuffer(&buffer);
    free(buffer_data);
}

//runs testAddRemove BUFFER_SIZE +1 times
void testAddRemoveMultiple()
{
    for(int i = 0; i < BUFFER_SIZE +1; i ++)
    {
        TEST_RUN(testAddRemove);
    }
}

//tries to find data in an empty buffer
//test succeeds if the contains() function returns INT_MIN
void testContains()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    TEST_ASSERT(contains(&buffer, 1) == INT_MIN, "test \t buffer contains %d\n\t", 
            INT_MIN);
    printBuffer(&buffer);
    free(buffer_data);
}

//adds a value to the buffer and then tries to find it with contains
//test succeeds if contains returns the value
void testAddContains()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    int val = 1;
    int ret;

    addElement(&buffer,val);
    ret = contains(&buffer, val);

    TEST_ASSERT(ret == val, "test \t added %d\n\t buffer contains %d\n\t", 
            val, ret);
    printBuffer(&buffer);
    free(buffer_data);

}

//adds two values to the buffer and the checks if the buffer contains the second value
//test succeeds if the contains function returns the second value
void testAddMultipleContains()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    int val1 = 1;
    int val2 = 2;
    int ret;
    addElement(&buffer,val1);
    addElement(&buffer,val2);

    ret = contains(&buffer, val2);

    TEST_ASSERT(val2 == ret, "test \t buffer contains %d\n\t", ret);
    printBuffer(&buffer);

    free(buffer_data);
}

//fills the buffer with data and then checks if the buffer contains the last value added
//the test succeeds if the contains function returns the last value added
void testAddFullContains()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    int temp;
    int ret;
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        addElement(&buffer, i);
    }
    temp = BUFFER_SIZE -1;
    ret = contains(&buffer,BUFFER_SIZE -1);
    printBuffer(&buffer);
    TEST_ASSERT(temp == ret, "test \t buffer contains %d \n\t", 
            temp);
    free(buffer_data);
}

//initializes a new buffer and then checks if the buffer contains the proper values 
//for maxLength, head, and tail
//test succeeds if the buffer contains the proper values 
void testInit()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    printf("white box test init\n");
    int maxLength = buffer.maxLength;
    int head = buffer.head;
    int tail = buffer.tail;
    TEST_ASSERT(maxLength == BUFFER_SIZE && head == 0 && tail == 0, 
            "test whitebox\n\t maxLength %d\n\t head %d\n\t tail %d\n\t",
            maxLength, head, tail);
    free(buffer_data);
}


void testAdd()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    printf("white box test add");
    addElement(&buffer, 1);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0,
            "test add one element to empty buffer\n\t expected head to be 0 \n\t expect tail to be 0 \t head :%d\n\t tail:%d \n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    addElement(&buffer, 1);
    removeHead(&buffer);
    addElement(&buffer,1);
    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, 
            "test\n\t expect head to be 0\n\t expect tail to be 0\n\t head: %d \n\t tail: %d \n\t",
            buffer.head, buffer.tail);

    addElement(&buffer, 1);
    TEST_ASSERT(buffer.head == 0 && buffer.tail == 1,
            "test at 2 elements\n\t expect head to be 0\n\t expect tail to be 1\n\t head: %d \n\t tail: %d\n",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    for(int i = 0; i < BUFFER_SIZE -1; i++)
    {
        addElement(&buffer, i);
    }
    TEST_ASSERT(buffer.head == 0 && buffer.tail == 2, 
            "test\n\t expect head to be 0\n\t expect tail to be 2\n\t head: %d \n\t tail: %d\n",
            buffer.head, buffer.tail);

    free(buffer_data);
}

void testRemoveValue()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    addElement(&buffer, 1);
    int ret = removeValue(&buffer, 2);

    TEST_ASSERT(buffer.head == 0&&buffer.tail == 0,
            "test expect head to be 0 \n\t expect tail to be 0\n\t head: %d \n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        addElement(&buffer, i);
    }
    removeValue(&buffer, 2);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 2, 
            "test \n\t expect head to be 0\n\t expect tail to be 2\n\t head: %d \n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    removeValue(&buffer,1);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, 
            "test \n\t expect head to 0 \n\t expect tail to be 0 \t head: %d \n\t tail: %d\n\t",
            buffer.head, buffer.tail);


    free(buffer_data);
}

void testRemoveHead()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    addElement(&buffer, 1);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, 
            "test \n\t expect head to be 0 \n\t expect tail to be 0\n\t head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);
    
    addElement(&buffer, 1);
    addElement(&buffer, 1);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 1 && buffer.tail == 1, 
            "test \n\t expect head to be 1 \n\t expect tail to be 0\n\t head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    addElement(&buffer, 1);
    addElement(&buffer, 1);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 2 && buffer.tail == 3, 
            "test \n\t expect head to be 2\n\t expect tail to be 0\n\t  head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, 
            "test \n\t expect head to be 0\n\t expect tail to be 0\n\t head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    free(buffer_data);
}

void app_main() {

    //blackbox tests
    TEST_RUN(testAddRemove);
    TEST_RUN(testAddRemove2);
    TEST_RUN(testAddRemoveFull);
    TEST_RUN(testAddDiscardOnFull);
    TEST_RUN(testAddRemoveMultiple);
    TEST_RUN(testContains);
    TEST_RUN(testAddContains);
    TEST_RUN(testAddMultipleContains);
    TEST_RUN(testAddFullContains);

    //whitebox tests
    TEST_RUN(testInit);
    TEST_RUN(testAdd);
    TEST_RUN(testRemoveValue);
    TEST_RUN(testRemoveHead);

}
