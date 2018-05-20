#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "LList.h"


NodeValues outDegreeCentrality(Graph g) {
    NodeValues *new = malloc(sizeof(NodeValues));
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        new->values[v] = countOut(g, v);
    }

    return new;
}

NodeValues inDegreeCentrality(Graph) {
    NodeValues *new = malloc(sizeof(NodeValues));
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        new->values[v] = countIn(g, v);
    }
    return new;
}

NodeValues degreeCentrality(Graph) {
    NodeValues *new = malloc(sizeof(NodeValues));
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        new->values[v] = countIn(g, v) + countOut(g, v);
    }
    return new;
}// for undirected graph

NodeValues closenessCentrality(Graph) {

}

NodeValues betweennessCentrality(Graph) {

}
NodeValues betweennessCentralityNormalised(Graph) {

}


void  showNodeValues(NodeValues v) {
    int i = 0;
    while(i < v->noNodes){
        printf("%lf ", v->values[i]);
        i++;
    }
}

void  freeNodeValues(NodeValues v) {
    free (v->values);
    free(v);
}
