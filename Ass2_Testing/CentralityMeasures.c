#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "CentralityMeasures.h"
//#include "Graph.c"

int count(AdjList L) {

    int c = 0;

    //counts number of nodes in edge list.
    while (L != NULL) {
        c++;
        L = L->next;
    }

    return c;
}

int countOut(Graph g, Vertex v) {
    return count(outIncident(g, v));
}

int countIn(Graph g, Vertex v) {
    return count(inIncident(g, v));
}


NodeValues outDegreeCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(new->noNodes, sizeof(double));
    assert(new->values != NULL);
    Vertex v;
    for (v = 0; v < new->noNodes; v++) {
        new->values[v] = countOut(g, v);
    }

    return *new;
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
    return *new;
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
    return *new;
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
    NodeValues throwAway = {0};
    return throwAway;
}

NodeValues betweennessCentrality(Graph g) {
    //one sympathy mark please
    NodeValues throwAway = {0};
    return throwAway;
}
NodeValues betweennessCentralityNormalised(Graph g) {
    NodeValues throwAway = {0};
    return throwAway;
}


void  showNodeValues(NodeValues v) {
    int i = 0;
    while(i < v.noNodes){
        printf("%lf ", v.values[i]);
        i++;
    }
}

void  freeNodeValues(NodeValues v) {
    free (v.values);
    //free(v);
}
