#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "single_linked_list.h"
#include "double_linked_list.h"

#define TEST_ASSERT(test, ...)                                                   \
    do                                                                           \
    {                                                                            \
        printf(__VA_ARGS__);                                                     \
        if (!(test))                                                             \
        {                                                                        \
            printf("Aseertion Failed: (%s), func %s, file %s, line %d\n", #test, \
                   __FUNCTION__, __FILE__, __LINE__);                            \
        }                                                                        \
        else                                                                     \
        {                                                                        \
            printf("\tPassed\n");                                                \
        }                                                                        \
    } while (0)
#define TEST_RUN(test)               \
    do                               \
    {                                \
        printf("TEST: %s\n", #test); \
        test();                      \
    } while (0)

//TODO blackbox Test SLL init
void testSLLInit()
{
    struct singleLinkedList list;
    initSLL(&list);

    int ret = removeFirstSLL(&list);

    TEST_ASSERT(ret == INT_MIN, "test init returned %d\n", ret);
}
//TODO blackbox Test SLL add
void testSLLAdd()
{
    int val = 1;
    struct singleLinkedList list;
    initSLL(&list);

    int ret = addSLL(&list, val);
    ret = removeFirstSLL(&list);

    TEST_ASSERT(ret == val, "test add returned %d\n", ret);
}
//TODO blackbox Test SLL remove
void testRemoveLast()
{
    int val = 1;
    struct singleLinkedList list;
    initSLL(&list);
    addSLL(&list, val);
    addSLL(&list, val);

    int ret = removeLastSLL(&list);

    TEST_ASSERT(ret == val," test remove last returned %d\n",ret);
}
void testRemoveFirst()
{
    int val = 1;
    struct singleLinkedList list;
    initSLL(&list);
    addSLL(&list, val);
    addSLL(&list, val);

    int ret = removeFirstSLL(&list);

    TEST_ASSERT(ret == val," test remove first returned %d\n",ret);
}
//test DLLInit
void testDLLInit()
{
    struct doubleLinkedList list;
    initDLL(&list);

    int val = removeFirstDLL(&list);

    TEST_ASSERT(val == INT_MIN, "test init DLL returned %d\n", val);
}
//TODO blackbox Test DLL add
void testDLLAdd()
{
    int val = 1;
    struct doubleLinkedList list;
    initDLL(&list);

    int ret = addDLL(&list, val);
    ret = removeFirstDLL(&list);

    TEST_ASSERT(ret == val, "test add DLL returned %d\n", ret);
}
//TODO blackbox Test DLL remove
void testRemoveLastDLL()
{
    int val = 1;
    struct doubleLinkedList list;
    initDLL(&list);
    addDLL(&list, val);
    addDLL(&list, val);

    int ret = removeLastDLL(&list);
    TEST_ASSERT(ret == val," test remove last DLL returned %d\n",ret);
}
void testRemoveFirstDLL()
{
    int val = 1;
    struct doubleLinkedList list;
    initDLL(&list);
    addDLL(&list, val);
    addDLL(&list, val);

    int ret = removeFirstDLL(&list);
    TEST_ASSERT(ret == val," test remove first DLL returned %d\n",ret);
}
//TODO whitebox Test SLL init
//TODO whitebox Test SLL add
//TODO whitebox Test SLL remove
//
//TODO whitebox Test DLL init
//TODO whitebox Test DLL add
//TODO whitebox Test DLL remove
//TODO 

void app_main() {



}
