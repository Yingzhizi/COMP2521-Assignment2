#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "CentralityMeasures.h"
//#include "Graph.c"

int count(AdjList L) {

    int c = 0;

    //counts number of nodes in edge list.
    adjListNode *curr = L;
    while (curr != NULL) {
        c++;
        curr = curr->next;
    }

    return c;
}

int countOut(Graph g, Vertex v) {
    return count(outIncident(g, v));
}

int countIn(Graph g, Vertex v) {
    return count(inIncident(g, v));
}

double countOutW(Graph g, Vertex v){
    double totalWeight = 0;
    //ShortestPaths *sp = malloc(sizeof(ShortestPaths));
    //assert(sp != NULL);
    //getting shortest path

    ShortestPaths sp = dijkstra(g, v);

    //weight will change depending on where we are

    //get all closeness noNode
    // AdjList out = outIncident(g, v);
    // while (out != NULL) {
    //     totalWeight += out->weight;
    //     out = out->next;
    // }

    for(int j = 0; j < sp.noNodes; j++){
        totalWeight += sp.dist[j];
    }

    return totalWeight;
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
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);
    Vertex v;
    for (v = 0; v < numVerticies(g); v++) {
        new->values[v] = countIn(g, v);
    }
    return *new;
}

NodeValues degreeCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);
    Vertex v;
    for (v = 0; v < numVerticies(g); v++) {
        new->values[v] = countIn(g, v) + countOut(g, v);
    }
    return *new;
}// for undirected graph

NodeValues closenessCentrality(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);
    ShortestPaths *sp = malloc(sizeof(struct ShortestPaths));
    assert(sp != NULL);
    Vertex v;
    // int weight, noOutEdges, noInEdges;
    for (v = 0; v < numVerticies(g); v++){
        // weight = countOutW(g, v);
        // noOutEdges = countOut(g, v);
        new->values[v] = (numVerticies(g) - 1) / countOutW(g, v);
    }
    return *new;
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
        printf("%d: %lf\n", i, v.values[i]);
        i++;
    }
}

void  freeNodeValues(NodeValues v) {
    free (v.values);
    //free(v);
}
