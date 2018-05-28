#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "PQ.h"
#include "Graph.h"

#define INF 0x7FFFFFFF


//Using a priority queue in form a linked list.
typedef struct PQRep {
    struct PQNode *head;
    struct PQNode *last;
} PQRep;

typedef struct PQNode {
    ItemPQ item;
    struct PQNode *next;
} PQNode;




/**
  * This function is used to create a new priority queue, that
  * can store items of type ItemPQ.
  *
  */
PQ newPQ() {

    //creates a new empty priority queue and makes sure
    //it is valid
    PQRep *new = malloc(sizeof(PQRep));
    assert (new != NULL);

    //initialise the head and last of a new priority queue
    new->head = NULL;
    new->last = NULL;

    return new;
}

/**
  * Adds item (ItemPQ) to the priority queue.
  * If the item's key already exist then update it's value.
  *
  */
void addPQ(PQ q, ItemPQ item) {

    assert (q != NULL);

    //Checks to see whether there is an existing key
    //makes a curr pointer to beginning of priority queue
    PQNode *curr = q->head;

    //run through the entire priority queue
    while (curr != NULL) {
        //if the key does exist then update the value
        if (curr->item.key == item.key) {
            curr->item.value = item.value;
            return;
        }
        //move through the linked list
        curr = curr->next;
    }

    //If an item with 'key' doesn't exists
    //we need to insert it

    //make a new node to insert into priority queue and make sure
    //it is valid
    PQNode *new = malloc(sizeof(PQNode));
    assert(new != NULL);

    //initialise the node with the right key and value.
    new->item.key = item.key;
    new->item.value = item.value;
    new->next = NULL;

    //adding to the priority queue
    //adding to an empty priority queue
    if (q->head == NULL) {
        //It becomes the only item in the queue
        q->head = q->last = new;
        return;
    }

    //adding to front of the priority queue
    if (q->head->item.key > item.key) {
        new->next = q->head;
        q->head = new;
        return;

    //adding to the back of the priority queue
    } else if (q->last->item.key < item.key) {
        q->last->next = new;
        q->last = new;
        return;

    //adding to the middle of the priority queue
    } else {
        curr = q->head;
        PQNode *prev = NULL;
        while (curr != NULL) {
            if (curr->item.key > item.key) {
                prev->next = new;
                new->next = curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }

}

/**
  * Removes and returns the item (ItemPQ) with the smallest 'value'.
  * For items with equal 'value', observes FIFO. Returns NULL if
  * queue is empty.
  *
  */
ItemPQ dequeuePQ(PQ q) {

    assert (q != NULL);

    //since ItemPQ can't be NULL, assert to make sure
    //it isn't NULL
    assert (PQEmpty(q) != 1);

    //make PQNode temporary pointers one for traversing the
    //priority queue and one used to remove the node
    PQNode *curr = q->head;
    PQNode *tmp = NULL;

    //removing the only item in the priority queue
    if(q->head == q->last){
        //update the priority queue and return the value dequeued
        q->head = q->last = NULL;
        return curr->item;

    //if PQ size is > 1
    } else {

        //these are used to keep track of smallest value and 
        //it's key
        int smallest = INF;
        int keyIndex;

        curr = q->head;

        //run through the whole priority queue
        while(curr != NULL){
            //try and find the smallest value in the priority queue
            if(curr->item.value < smallest){
                //keep track of the smallest value and it's key
                keyIndex = curr->item.key;
                smallest = curr->item.value;
            }
            curr = curr->next;
        }

        PQNode *prev = NULL;
        curr = q->head;

        //as each key is unique, use the key to find the item
        //that needs to be removed
        while(curr != NULL){
            //stop and break at item that needs to be removed
            if(curr->item.key == keyIndex){
                break;
            }
            //if item isn't found move to the next item
            //in the list
            prev = curr;
            curr = curr->next;
        }

        //store the item needed to be dequeued and returned
        tmp = curr;

        //removing the item
        //item being removed is head
        if (prev == NULL) {
            //update the pointers
            q->head = curr->next;

        //item being removed is at last
        } else if (curr == q->last) {
            //update the pointers
            q->last = prev;
            prev->next = NULL;

        //item being removed is somewhere in the middle
        } else {
            prev->next = curr->next;
        }
        //avoid memory leaks
        free(curr);
    }

    return tmp->item;
}

/**
  * Updates item with a given 'key' value, by updateing the item's
  * value, by updating the item's value to the given 'value'.
  * If item with 'key' does not exist in the queue, no action is taken.
  *
  */
void updatePQ(PQ q, ItemPQ item) {

    assert (q != NULL);

    //make a curr to traverse the priority queue
    PQNode *curr = q->head;

    //run through the whole priority queue
    while (curr != NULL) {
        //if the key already exist then update the value
        //if key doesn't exist we dont do anything
        if (curr->item.key == item.key) {
            curr->item.value = item.value;
        }
        //move to the next item in the priority queue
        curr = curr->next;
    }
}

/**
  * Checks to see whether the priority queue is empty. If it is
  * return 1, otherwise return 0.
  *
  */
int PQEmpty(PQ q) {

    if(q->head == NULL){
        return 1;
    }
    return 0;
}

/**
  * Displays what the priority queue looks like.
  * It displays only ItemPQ's value in the form of
  * value 1 > value2 > value3 > ...etc
  *
  */
void  showPQ(PQ q) {

    //if priority queue is empty then
    //print a new line and exit the function
    if(PQEmpty(q) == 1){
        puts("\n");
        return;
    }

    PQNode *curr = q->head;

    //print out the values of the priority queue
    while(curr->next != NULL){
        printf("%d > ", curr->item.value);
        curr = curr->next;
    }
    printf("%d\n", curr->item.value);
}

/**
  * Frees the priority queue.
  *
  */
void  freePQ(PQ q) {

    PQNode *curr = q->head;
    PQNode *tmp;
    while (curr != NULL) {
        tmp = curr->next;
        //free(curr->item);
        curr = tmp;
    }
    free(q);
}
