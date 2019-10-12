#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
typedef struct ListNode{
    void* data;
    struct ListNode* next;
    struct ListNode* previous;
} ListNode;
typedef struct{
    struct ListNode* head;
    struct ListNode* tail;
    int count;
} LinkedList;
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
