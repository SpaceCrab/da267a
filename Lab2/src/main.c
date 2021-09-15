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

void blackBoxTest1()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    int added = addElement(&buffer, 3);
    int removed = removeHead(&buffer);

    TEST_ASSERT(added == removed, "test \tadd element %d\n \tremoved %d\n", added, removed);

    printBuffer(&buffer);
    free(buffer_data);
//    if(added == removed)
//    {
//        printf("\n\n\n");
//        printf("bb1 pass");
//        printf("\n\n\n");
//    }
//    else{
//        printf("\n\n\n");
//        printf("bb1 failed");
//        printf("\n\n\n");
//    }

}

void blackBoxTest2()
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
//   assert(valAdd1 == valRem1);
//   assert(valAdd2 == valRem2);
}

void blackBoxTest3()
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
//        assert(i == removeHead(buffer));
        TEST_ASSERT(i == temp, "test \t add element %d \n\t removed %d\n\t",
                i, temp );
    }
    printBuffer(&buffer);
    free(buffer_data);
}

void blackBoxTest4()
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
//    assert(removeHead(&buffer) == BUFFER_SIZE +1);
    printBuffer(&buffer);
    free(buffer_data);
}

void blackBoxTest5()
{
    for(int i = 0; i < BUFFER_SIZE +1; i ++)
    {
        TEST_RUN(blackBoxTest1);
    }
}

void blackBoxTest6()
{
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    TEST_ASSERT(contains(&buffer, 1) == INT_MIN, "test \t buffer contains %d\n\t", 
            INT_MIN);
    printBuffer(&buffer);
    free(buffer_data);
}

void blackBoxTest7()
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

void blackBoxTest8()
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

void blackBoxTest9()
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
//    assert(removeHead(&buffer) == BUFFER_SIZE +1);
    free(buffer_data);
}

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

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, "test add one element to empty buffer \t head :%d\n\t tail:%d \n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    addElement(&buffer, 1);
    removeHead(&buffer);
    addElement(&buffer,1);
    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, "test \t head: %d \n\t tail: %d \n\t",
            buffer.head, buffer.tail);

    addElement(&buffer, 1);
    TEST_ASSERT(buffer.head == 0 && buffer.tail == 1, "test at 2 elements \t head: %d \n\t tail: %d\n",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    for(int i = 0; i < BUFFER_SIZE -1; i++)
    {
        addElement(&buffer, i);
    }
    TEST_ASSERT(buffer.head == 0 && buffer.tail == 2, "test \t head: %d \n\t tail: %d\n",
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

    TEST_ASSERT(buffer.head == 0&&buffer.tail == 0, "test \t head: %d \n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        addElement(&buffer, i);
    }
    removeValue(&buffer, 2);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 2, "test \t head: %d \n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    removeValue(&buffer,1);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, "test \t head: %d \n\t tail: %d\n\t",
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

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, "test \t head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);
    
    addElement(&buffer, 1);
    addElement(&buffer, 1);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 1 && buffer.tail == 1, "test \t  head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    addElement(&buffer, 1);
    addElement(&buffer, 1);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 2 && buffer.tail == 3, "test \t  head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);
    removeHead(&buffer);

    TEST_ASSERT(buffer.head == 0 && buffer.tail == 0, "test \t  head: %d\n\t tail: %d\n\t",
            buffer.head, buffer.tail);

    free(buffer_data);
}

void app_main() {

    // Some code to help you get started
    struct circularBuffer buffer;
    int *buffer_data = (int*) malloc(BUFFER_SIZE * sizeof(int));
    initCircularBuffer(&buffer, buffer_data, BUFFER_SIZE, 0);

    TEST_RUN(blackBoxTest1);
    TEST_RUN(blackBoxTest2);
    TEST_RUN(blackBoxTest3);
    TEST_RUN(blackBoxTest4);
    TEST_RUN(blackBoxTest5);
    TEST_RUN(blackBoxTest6);
    TEST_RUN(blackBoxTest7);
    TEST_RUN(blackBoxTest8);
    TEST_RUN(blackBoxTest9);

    TEST_RUN(testInit);
    TEST_RUN(testAdd);
    TEST_RUN(testRemoveValue);
    TEST_RUN(testRemoveHead);

//
//
//    printf("\n\n\n");
//    printf("For example, output the results of your tests here.");
//    
//    printf("\n\n");   
//
//    printf("\nPerhaps with some delay...");
//
//    printf("\n\n\n");
//
//    ets_delay_us(2000000ul);
//    printf("\nbetween your printouts!");
//
//
//    printf("\n\n\n");

    free(buffer_data);
}
