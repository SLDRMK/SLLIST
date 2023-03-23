#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100

typedef int NodeType;
int length = 0;

typedef struct SLLISTNode
{
    NodeType data;
    struct SLLISTNode* next;
} Node, * pNode, ** ppNode;

pNode newNode(NodeType x);
pNode end(pNode head);
int num(pNode head);
void print(pNode head);
void printc(pNode head);
void add(ppNode head, NodeType x);
pNode delete(ppNode head, int index);
pNode deleteRange(ppNode head, NodeType mink, NodeType maxk);
pNode deleteRangeOrderly(ppNode head, NodeType mink, NodeType maxk);
void releaseList(ppNode head);
pNode reverse(ppNode head);
pNode addHead(ppNode head, NodeType x);
pNode modifyOrderly(ppNode heada, pNode headb, pNode headc);
int locateOrderly(pNode head, NodeType x);

// make a new Node
pNode newNode(NodeType x)
{
    pNode temp = (pNode)malloc(sizeof(Node));
    temp->data = x;
    temp->next = NULL;
    return temp;
}

// return the end of head
pNode end(pNode head)
{
    if (!head)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

// return the length of the list and update the value length
int num(pNode head)
{
    length = 0;
    pNode temp = head;
    while (temp)
        temp = temp->next, length++;
    return length;
}

// print the whole list as integers with blank intervals
void print(pNode head)
{
    pNode temp = head;
    if (!head)
    {
        printf("NULL");
        return;
    }
    while (temp->next)
        printf("%d ", temp->data), temp = temp->next;
    printf("%d", temp->data);
}

// print the whole list as characters with comma intervals
void printc(pNode head)
{
    pNode temp = head;
    if (!head)
    {
        printf("NULL");
        return;
    }
    while (temp->next)
        printf("%c,", temp->data), temp = temp->next;
    printf("%c", temp->data);
}

// add a new Node in the end
void add(ppNode head, NodeType x)
{
    pNode tail = newNode(x);
    pNode last;
    last = end(*head);
    last->next = tail;
    length++;
}

// delete the certain Node by index, which starts from zero and return the new list
pNode delete(ppNode head, int index)
{
    pNode temp = *head;
    pNode temp1 = *head;
    if (!index)
    {
        temp1 = temp1->next, free(temp);
        return temp1;
    }
    while (--index)
        temp = temp->next;
    pNode x = temp->next;
    if (!x)
        temp->next = NULL;
    else
        temp->next = x->next;
    free(x);
    length--;
    return *head;
}

// delete the Nodes with data that are in the range of (mink, maxk) and return the new list
pNode deleteRange(ppNode head, NodeType mink, NodeType maxk)
{
    pNode temp = NULL;
    pNode pointer = *head;
    while (pointer && (pointer->data > mink && pointer->data < maxk))
        pointer = pointer->next;
    if (!pointer)
        return NULL;
    temp = newNode(pointer->data);
    pointer = pointer->next;
    while (pointer)
    {
        if (pointer->data <= mink || pointer->data >= maxk)
            add(&temp, pointer->data);
        pointer = pointer->next;
    }
    releaseList(head);
    return temp;
}

// delete the Nodes with data that are in the range of (mink, maxk) in a oroderly list and return the new list
pNode deleteRangeOrderly(ppNode head, NodeType mink, NodeType maxk)
{
    pNode temp = *head;
    pNode temp0 = NULL, temp1 = NULL;
    if (!temp)
        return NULL;
    while (temp->next && temp->next->data <= mink)
        temp = temp->next;
    if (temp)
        temp0 = temp;
    while (temp0->next && temp0->next->data < maxk)
        temp0 = temp0->next;
    temp->next = temp0->next;
    temp0->next = NULL;
    releaseList(&temp);
    return *head;
}

// reverse the whole list and return the new list
pNode reverse(ppNode head)
{
    pNode pointer = *head, temp = NULL;
    while (pointer)
        temp = addHead(&temp, pointer->data), pointer = pointer->next;
    pointer = *head;
    releaseList(&pointer);
    return temp;
}

// add a Node before the whole list and return the new list
pNode addHead(ppNode head, NodeType x)
{
    pNode newHead = newNode(x);
    newHead->next = *head;
    *head = newHead;
    return *head;
}

// release the space occupied by the list
void releaseList(ppNode head)
{
    pNode temp = *head;
    pNode pointer = temp;
    while (!temp)
    {
        temp = temp->next;
        free(pointer);
        pointer = temp;
    }
}

// delete the Nodes in the heada that have the same data both in headb and headc
pNode modifyOrderly(ppNode heada, pNode headb, pNode headc)
{
    pNode temp = *heada;
    NodeType tempData;
    int index = 0;
    while (temp)
    {
        tempData = temp->data;
        temp = temp->next;
        if (locateOrderly(headb, tempData) > -1 && locateOrderly(headc, tempData) > -1)
            *heada = delete(heada, index), index--;
        index++;
    }
    return *heada;
}

// locate a certain datum in the list and return its first index (start from 0); if it doesn't exist, return -1
int locateOrderly(pNode head, NodeType x)
{
    pNode temp = head;
    if (!temp)
        return -1;
    int index = 0;
    while (temp->next && temp->next->data <= x)
        temp = temp->next, index++;
    if (temp->data != x)
        return -1;
    return index;
}

// test function
void main()
{
    pNode list = newNode(1);
    add(&list, 2);
    add(&list, 4);
    add(&list, 6);
    add(&list, 25);
    add(&list, 26);
    print(list);
    printf("\n");
    pNode list1 = newNode(1);
    add(&list1, 2);
    add(&list1, 5);
    add(&list1, 6);
    add(&list1, 10);
    pNode list2 = newNode(1);
    add(&list2, 2);
    add(&list2, 6);
    add(&list2, 12);
    add(&list2, 25);
    list = modifyOrderly(&list, list1, list2);
    print(list);
}