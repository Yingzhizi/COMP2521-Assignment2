#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "PQ.h"
#define INF 0x7FFFFFFF

typedef struct PQRep {
    struct PQNode *head;
    struct PQNode *last;
} PQRep;

typedef struct PQNode {
    ItemPQ item;
    struct PQNode *next;
} PQNode;

/* Creates new priority queue, that can store items of type ItemPQ.
*/
PQ newPQ() {
    PQRep *new = malloc(sizeof(PQRep));
    assert (new != NULL);
    new->head = NULL;
    new->last = NULL;
    return new;
}

/* Adds item (ItemPQ) to the priority queue.
   If an item with 'key' exists, it's 'value' is updated.
*/
void addPQ(PQ q, ItemPQ item) {
    assert (q != NULL);

    PQNode *curr = q->head;
    while (curr != NULL) {
        if (curr->item->key == item->key) {
            curr->item->value = item->value;
            return;
        }
        curr = curr->next;
    }

    //If an item with 'key' doesn't exists
    //we need to insert a new node
    PQNode *new = malloc(sizeof(PQNode));
    new->key = item->key;
    new->value = item->value;

    //if the q is empty
    if (q->head == NULL) {
        q->head = q->last = new;
        return;
    }

    if (q->head->key > item->key) {
        new->next = q->head;
        q->head = new;
        return;
    } else if (q->last->key < item->key) {
        q->last->next = new;
        q->last = new;
        return;
    } else {
        curr = q->head;
        PQNode *prev = NULL;
        while (curr != NULL) {
            if (curr->item->key > item->key) {
                prev->next = new;
                new->next = curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

ItemPQ dequeuePQ(PQ q) {
    assert (q != NULL);
    //
    if (PQEmpty(q)) return NULL;
    PQNode *curr = q->head;

    if(q->head == q->last){
        q->head = q->last = NULL;
        return curr->item;
    } else {
        int smallest = INF;
        int keyIndex;
        curr = q->head;
        while(curr != NULL){
            //get the smallest value and track the key
            if(curr->item->value < smallest){
                keyIndex = curr->item->key;
                smallest = curr->item->value;
            }
            curr = curr->next;
        }
        PQNode *prev = NULL;
        curr = q->head;
        while(curr != NULL){
            //remove the item
            if(curr->item->key == keyIndex){
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        PQNode * tmp = curr;
        if (prev == NULL) {
            q->head = curr->next;
        } else if (curr == q->last) {
            q->last = prev;
            prev->next = NULL;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }
    return tmp;
}

void updatePQ(PQ q, ItemPQ item) {
    assert (q != NULL);
    PQNode *curr = q->head;
    while (curr != NULL) {
        if (curr->item->key == item->key) {
            curr->item->value = item->value;
        }
        curr = curr->next;
    }
}

int PQEmpty(PQ q) {
     if(q->head == NULL){
         return 1;
     }
     return 0;
}

void  showPQ(PQ q) {
    PQNode *curr = q->head;
    while(curr->next != NULL){
        printf("%d > ", curr->item->value);
        curr = curr->next;
    }
    printf("%d\n", curr->item->value);
}

void  freePQ(PQ q) {
    PQNode *curr = q->head;
    PQNode *tmp;
    while (curr != NULL) {
        tmp = curr->next;
        free(curr->items);
        curr = tmp;
    }
    free(q);
}
