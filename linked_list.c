/******************************
* Linked List Data Structure
* Responisble for holding a dynamic list in memory across nodes
* Generic and takes function pointers to format or free data according to needs

* Author: retro-node

* Date Created: 27/09/2019
* Last Modified: 03/10/2019

03/10/2019 - Added function to return node data according to position in list,
    added null guard to printLinkedList() LL parameter.
02/10/2019 - Added function to return length of linked list

*******************************/

#include "linked_list.h"

/**********
* Creates Linked List - will require free
* returns pointer to Linked List struc
**********/
LinkedList* createLinkedList(void)
{
    LinkedList* ll = (LinkedList*)calloc(1,sizeof(LinkedList));
    ll-> head = NULL;
    ll-> tail = NULL;
    ll->count = 0;
    return ll;
}
/* shorthand creation of node for easier writing */
ListNode* createNode(void* data, ListNode* prev, ListNode* next)
{
    ListNode* newnode = (ListNode*)calloc(1,sizeof(ListNode));
    newnode->data = data;
    newnode->next = next;
    newnode->previous = prev;
    return newnode;
}
/*******
* Inserts data into first node in LL
* Each node is calloc'ed and requires free
*******/
void insertStart(LinkedList* ll, void* data)
{
    ListNode* newnode;
    /*1. list is empty, 2. only 1 node exists in ll, 3. is populated*/
    if(ll->count == 0)
    {
        /*set both head and tail to new node with data */
        newnode = createNode(data, NULL, NULL);
        ll->head = newnode;
        ll->tail = newnode;
        ll->count ++;
    }
    else if(ll->count == 1) /* head and tail point same place - 1 node*/
    {
        /*create new node and set head.next to new node and make it the tail*/
        newnode = createNode(data, NULL, ll->tail);
        ll->head = newnode;
        ll->tail->previous = newnode;
        ll->count ++;
    }
    else /* neither apply and populated list */
    {
        /* create new node, set previous to NULL and next to current head
         * put in data and set it as head of LL as insertfirst */
        newnode = createNode(data, NULL, ll->head);
        ll->head = newnode;
        ll->count++;
    }

}
/************
* Remove head node from LL setting it to the next node in the list
***********/
void* removeStart(LinkedList* ll)
{
    /* Sets head to head->next, frees old head before setting to null
    * Decrement count
    Conditions:
        1. empty list
        2. single node
        3. populated
    */
    void* data;
    data = NULL;
    if(ll->head == NULL)
    {
        printf("Empty List: cannot remove node.\n");
    }
    else if(ll->head == ll->tail) /*head is not null and is same as tail - 1 node */
    {
        data = ll->head->data; /* get the data*/
        free(ll->head);        /* free the node */
        ll->head = NULL;    /* make list empty*/
        ll->tail = NULL;
        ll->count--;        /* decrement count - should be zero */
        if(ll->count != 0)
        {
            perror("Lost track of node count");
        }
    }
    else
    {
        data = ll->head->data;      /* get data */
        ll->head = ll->head->next;  /* move head */
        free(ll->head->previous);
        ll->head->previous = NULL;
        ll->count--;
    }
    return data;
}
/*********
* Inserts node after tail and set it to new tail
*********/
void insertLast(LinkedList* ll, void* data)
{
    /* Create new node with data, set it's previous to tail and next to NULL
    *  set tail to new node - increment count
    */
    ListNode* newnode = NULL;
    if(ll->count == 0)
    {
        newnode = createNode(data, NULL, NULL);
        ll->tail = newnode;
        ll->head = newnode;
    }
    else /* if tail is none then list is empty */
    {
        newnode = createNode(data, ll->tail, NULL);
        ll->tail->next = newnode;
        ll->tail = newnode;

    }
    ll->count ++;
}
/********
* Removes last node and moves tail to second last prior delete
*******/
void* removeLast(LinkedList* ll)
{
    /* gets data, sets node next to NULL, moves tail */
    /* 1. empty 2. single node 3. populated */
    void* data;
    data = NULL;
    if(ll->count == 0)
    {
        /* empty */
        printf("Empty List: Cannot remove node.\n");
    }
    else if(ll->count ==1)
    {
        data = ll->tail->data;
        free(ll->tail);
        ll->tail = NULL;
        ll->head = NULL;
        ll->count --; /*should be zero*/
        if(ll->count != 0)
        {
            perror("Lost track of number of ListNodes!");
        }
    }
    else /* works for single and multi populated list */
    {
        data = ll->tail->data;
        ll->tail = ll->tail->previous;
        free(ll->tail->next);
        ll->tail->next = NULL;
        ll->count--;
    }
    return data;
}
/*********
* Prints the LL head to tail to retain order
*********/
void printLinkedList(LinkedList* ll, dataMan printData)
{
    void* data;
    ListNode* node;
    if(ll!= NULL)
    {
        node = ll->head;
        while(node != NULL)
        {
            data = node->data;
            printData(data);
            node = node->next;
        }
    }
    else
    {
        printf("List is empty!");
    }
}
/********
* Free's the space used by the linked list calloc's
********/
void freeLinkedList(LinkedList* ll, dataMan processData)
{
    void* data;
    ListNode* node, *curNode;
    node = ll->head;
    while(node != NULL)
    {
        data = node->data;
        processData(data);           /* Give the data to dataMan func point */
        curNode = node->next;
        free(node);                  /* FREE */
        node = curNode;
    }
    free(ll); /* free list when clear */
    /*printf("Attention: List Freed!\n"); Disabled as not applicable with TTT*/
}

/************
* Returns length of linked list parsed
* Iterates through the list until node is NULL, returns iterator integer i
*/
int getListLength(LinkedList* ll)
{
    /*int i = 0;
    ListNode* node = ll->head;
    while(node != NULL)
    {
        i++;
        node = node->next;

    }*/
    return ll->count;
}

/*********
* Returns the data in place i within list
* For use within for loops to access the complete list or to access a specific
 node.
* Use sparingly, more expensive that array access.
*/
void* accessNode(LinkedList* ll, int nodenum)
{
    int i;
    ListNode* node = ll->head;
    for(i=0; i<nodenum; i++)
    {
        node = node->next;
    }
    return node->data;
}
