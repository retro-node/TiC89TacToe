#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
/* Node struct, holds pointers to next and prev and the generic data*/
typedef struct ListNode{
    void* data;
    struct ListNode* next;
    struct ListNode* previous;
} ListNode;
/* List struct, contains pointers to first and last nodes and a count of nodes*/
typedef struct{
    struct ListNode* head;
    struct ListNode* tail;
    int count;
} LinkedList;
/* generic handler func pointer to outsource what to do with data */
typedef void (*dataMan)(void*);
LinkedList* createLinkedList();
void insertStart(LinkedList*, void*);
void* removeStart(LinkedList*);
void insertLast(LinkedList*, void*);
void* removeLast(LinkedList*);
void printLinkedList(LinkedList*, dataMan);
void freeLinkedList(LinkedList*, dataMan);
int getListLength(LinkedList*);
void* accessNode(LinkedList*, int);
#endif
