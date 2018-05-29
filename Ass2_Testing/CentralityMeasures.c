#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "CentralityMeasures.h"



/**
  * This helps us to count the number of nodes within the edges arrays.
  * Used to count the outgoing edges and incoming edges. Used in CentralityMeasures.
  *
  */
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

/**
  * Returns the amount of nodes in an outgoing edge
  * array from a given vertex. Used for CentralityMeasures.
  *
  */
int countOut(Graph g, Vertex v) {
    return count(outIncident(g, v));
}

/**
  * Returns the amount of ndoes in an ingoing edge array
  * from a given vertex. Used for CnetralityMeasures.
  *
  */
int countIn(Graph g, Vertex v) {
    return count(inIncident(g, v));
}

/**
  * Need to fix this function before commenting on it.
  *
  */
int reachable(Graph g, Vertex v){
    ShortestPaths sp = dijkstra(g, v);
    int count = 0;
    for(int i = 0; i < numVerticies(g); i++){
        if(sp.dist[i] != 0){
            count++;
        }
    }
    count += 1;
    return count;
}


double countOutW(Graph g, Vertex v){
    double totalWeight = 0;
    //ShortestPaths *sp = malloc(sizeof(ShortestPaths));
    //assert(sp != NULL);
    //getting shortest path
    Vertex w;
    ShortestPaths sp;
    for(w = 0; w < numVerticies(g); w++) {
        sp = dijkstra(g, v);
        totalWeight += sp.dist[w];
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
    double nodereach;
    double nodetotal;
    // int weight, noOutEdges, noInEdges;
    for (v = 0; v < numVerticies(g); v++){
        nodereach = reachable(g, v) - 1;
        nodetotal = numVerticies(g) - 1;
        new->values[v] = (nodereach * (reachable(g, v) - 1)) / ((numVerticies(g) - 1) * countOutW(g, v));
        if (nodereach == 0) {
            new->values[v] = 0;
        }
    }
    return *new;
}

//count how many path exists in graph start from src to dest
int countPath(Vertex src, Vertex dest) {

}

int inPath(Vertex src, Vertex dest) {
    //return 1 if in
    //return 0 if not
}

NodeValues betweennessCentrality(Graph g) {
    //one sympathy mark please
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);
    for (v = 0; v < numVerticies(g); v++){

        new->values[v] = (nodereach * (reachable(g, v) - 1)) / ((numVerticies(g) - 1) * countOutW(g, v));

    }

    NodeValues throwAway = {0};
    return throwAway;
}

NodeValues betweennessCentralityNormalised(Graph g) {
    // assert(g != NULL);
    // NodeValues *new = malloc(sizeof(NodeValues));
    // assert(new != NULL);
    // new->noNodes = numVerticies(g);
    // new->values = calloc(numVerticies(g), sizeof(double));
    // assert(new->values != NULL);
    // //
    // NodeValues tmp = betweennessCentrality(g);
    // Vertex v;
    // for (v = 0; v < new->noNodes; v++) {
    //     new->values[v] = tmp.values[v] / ((numVerticies(g) - 1) * (numVerticies(g) - 2));
    // }
    // return *new;
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
