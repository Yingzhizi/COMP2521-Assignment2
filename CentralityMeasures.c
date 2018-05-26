#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "LList.h"


NodeValues outDegreeCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    assert(new->values != NULL);
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        new->values[v] = countOut(g, v);
    }

    return new;
}

NodeValues inDegreeCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    assert(new->values != NULL);
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        new->values[v] = countIn(g, v);
    }
    return new;
}

NodeValues degreeCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    assert(new->values != NULL);
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        new->values[v] = countIn(g, v) + countOut(g, v);
    }
    return new;
}// for undirected graph

NodeValues closenessCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = g->nV;
    new->values = calloc(g->nV, sizeof(double));
    assert(new->values != NULL);
    ShortestPaths *sp = malloc(sizeof(struct ShortestPaths));
    assert(sp != NULL);
    Vertex v;
    // int weight, noOutEdges, noInEdges;
    for (v = 0; v < g->nV; v++){
        // weight = countOutW(g, v);
        // noOutEdges = countOut(g, v);
        new->values[v] = countOut(g, v) / countOutW(g, v);
    }
}

NodeValues betweennessCentrality(Graph g) {
    //one sympathy mark please
}
NodeValues betweennessCentralityNormalised(Graph g) {

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
