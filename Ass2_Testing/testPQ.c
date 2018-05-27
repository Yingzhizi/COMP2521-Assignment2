#include "PQ.h"
//#include "PQ.c"
#include <stdlib.h>
#include <stdio.h>

int main(){
    PQ g = newPQ();
    ItemPQ *new = malloc(sizeof(ItemPQ));
    new->key = 1;
    new->value = 9;

    addPQ(g, *new);
    new->key = 1;
    new->value = 19;
    addPQ(g, *new);

    new->key = 1;
    new->value = 10;
    addPQ(g, *new);

    new->key = 1;
    new->value = 18;
    addPQ(g, *new);

    new->key = 12;
    new->value = 1;
    addPQ(g, *new);


    dequeuePQ(g);
    dequeuePQ(g);
    dequeuePQ(g);
    // dequeuePQ(g);
    //dequeuePQ(g);
    // addPQ(g,12);
    // addPQ(g,4);
    // addPQ(g,8);
    // addPQ(g,6);
    // addPQ(g,9);
    // addPQ(g,9);
    // addPQ(g,15);
    // addPQ(g,1);

    // addPQ(g,11,10,324);
    // addPQ(g,12,14,12);
    // addPQ(g,13,19,13);
    // addPQ(g,14,17,1);
    // addPQ(g,15,15,6);
    // addPQ(g,16,16,99);
    // addPQ(g,17, 15,4);
    // addPQ(g,18,16,5);
    // addPQ(g,19,2,7);


    // dequeuePQ(g,1,2);
    // dequeuePQ(g,2,1);
    // dequeuePQ(g,4,2);
    // dequeuePQ(g,5,2);
    // dequeuePQ(g,6,1);
    // dequeuePQ(g,7,2);
    // dequeuePQ(g,8,2);
    // dequeuePQ(g,9,2);
    // dequeuePQ(g,10,3);
    // dequeuePQ(g,11,10);
    // dequeuePQ(g,12,14);
    // dequeuePQ(g,13,19);
    // dequeuePQ(g,14,17);
    // dequeuePQ(g,15,15);
    // dequeuePQ(g,16,16);
    // dequeuePQ(g,17, 15);
    // dequeuePQ(g,18,16);
    // dequeuePQ(g,19,2);
    showPQ(g);
    return EXIT_SUCCESS;
}
