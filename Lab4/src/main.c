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
    struct sll list;
    initSLL(&list);

    int ret = removeFirstSLL(&list);

    TEST_ASSERT(ret == INT_MIN, "test init returned %d\n", ret);
}
//TODO blackbox Test SLL add
void testSLLAdd()
{
    int val = 1;
    struct sll list;
    initSLL(&list);

    int ret = addSLL(&list, val);
    ret = removeFirstSLL(&list);

    TEST_ASSERT(ret == val, "test add returned %d\n", ret);
}
//TODO blackbox Test SLL remove
void testRemoveLast()
{
    int val = 1;
    struct sll list;
    initSLL(&list);
    addSLL(&list, val);
    addSLL(&list, val);

    int ret = removeLastSLL(&list);

    TEST_ASSERT(ret == val," test remove last returned %d\n",ret);
}
void testRemoveFirst()
{
    int val = 1;
    struct sll list;
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
void testSLLInitWhite()
{
    struct sll list;
    initSLL(&list);

    TEST_ASSERT (list.first == NULL, "SLL list struct first is NULL \n");
}

//TODO whitebox Test SLL add
void testSLLAddWhite()
{
    int data[] = {1,2,3,4};
    struct sll list;
    initSLL(&list);
    
    int ret = addSLL(&list, 1);
    ret = addSLL(&list, 2);
    ret = addSLL(&list, 3);
    ret = addSLL(&list, 4);

    struct sll_element* element = list.first;
    int i = 0;
    while(element != NULL){
        int val = data[i++];
        TEST_ASSERT ( element->data == val, "expected %d to be %d", element->data, val);
        element = element->next;
    }
    cleanSll(&list);
}
//TODO whitebox Test SLL remove 
void testSLLRemoveFirst()
{
    struct sll list;
    initSLL(&list);

    int ret = addSLL(&list, 1);

    ret = removeFirstSLL(&list);
    TEST_ASSERT(ret == 1, "expected %d to be 1 \n", ret);

    ret = removeFirstSLL(&list);
    TEST_ASSERT(ret == INT_MIN, "expected %d to be %d \n", ret, INT_MIN);
    
    cleanSll(&list);
}

void testSLLRemoveLast()
{
    struct sll list;
    initSLL(&list);

    int ret = addSLL(&list, 1);

    ret = removeFirstSLL(&list);
    TEST_ASSERT(ret == 1, "expected %d to be 1 \n", ret);

    ret = removeFirstSLL(&list);
    TEST_ASSERT(ret == INT_MIN, "expected %d to be %d \n", ret, INT_MIN);
    
    cleanSll(&list);
}
//TODO whitebox Test DLL init
void testDLLInitWhite()
{
    struct doubleLinkedList list;
    initDLL(&list);

    TEST_ASSERT (list.first == NULL && list.last == NULL, "DLL list struct first is NULL \n");
}

//TODO whitebox Test DLL add
void testDLLAddWhite()
{
    int data[] = {1,2,3,4};
    struct doubleLinkedList list;
    initDLL(&list);
    
    int ret = addDLL(&list, 1);
    ret = addDLL(&list, 2);
    ret = addDLL(&list, 3);
    ret = addDLL(&list, 4);

    struct dllElement* element = list.first;
    int i = 0;
    while(element != NULL){
        int val = data[i++];
        TEST_ASSERT ( element->data == val, "expected %d to be %d", element->data, val);
        element = element->next;
    }
    cleanDll(&list);
}

void app_main() {
    printf("init\n");

    TEST_RUN(testSLLInit);
    TEST_RUN(testSLLAdd);
    printf("test SLLAdd done\n");
    TEST_RUN(testRemoveLast);
    TEST_RUN(testRemoveFirst);
    printf("test remove done!\n");
    TEST_RUN(testDLLInit);
    TEST_RUN(testDLLAdd);
    TEST_RUN(testRemoveLastDLL);
    TEST_RUN(testRemoveFirstDLL);
    TEST_RUN(testSLLInitWhite);
    TEST_RUN(testSLLAddWhite);
    TEST_RUN(testDLLInitWhite);
    TEST_RUN(testDLLAddWhite);
    printf("all tests done!!");
}
