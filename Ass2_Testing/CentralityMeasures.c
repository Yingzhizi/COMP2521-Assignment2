#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "CentralityMeasures.h"


int countNode(AdjList L);
int countOut(Graph g, Vertex v);
int countIn(Graph g, Vertex v);
int countReachable(Graph g, Vertex v);
double outWeight(Graph g, Vertex v);

double countPath(Graph g, Vertex s, Vertex t);
double countPathVia(Graph g, Vertex s, Vertex t, Vertex v);
double countPathHelper(ShortestPaths sp, Vertex s, Vertex t);
double countPathViaHelper(ShortestPaths sp, Vertex s, Vertex t, Vertex v);

// count the number of outgoing edges of every vertex in a given graph
NodeValues outDegreeCentrality(Graph g) {
    assert(g != NULL);

    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);

    int nV = numVerticies(g);
    new->noNodes = nV;
    new->values = calloc(nV, sizeof(double));
    assert(new->values != NULL);

    Vertex v;
    for (v = 0; v < new->noNodes; v++) {

        // countOut is a helper function
        new->values[v] = countOut(g, v);
    }

    return *new;
}

// count the number of incoming edges of every vertex in a given graph
NodeValues inDegreeCentrality(Graph g) {
    assert(g != NULL);

    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);

    int nV = numVerticies(g);
    new->noNodes = nV;
    new->values = calloc(nV, sizeof(double));
    assert(new->values != NULL);

    Vertex v;
    for (v = 0; v < nV; v++) {

        // countIn is a helper function
        new->values[v] = countIn(g, v);
    }

    return *new;
}

// count the sum of incoming edges and outgoing edges
// of every vertex in a given graph
NodeValues degreeCentrality(Graph g) {
    assert(g != NULL);

    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);

    int nV = numVerticies(g);
    new->noNodes = nV;
    new->values = calloc(nV, sizeof(double));
    assert(new->values != NULL);

    Vertex v;
    for (v = 0; v < nV; v++) {

        // Degree(v) = inDegree(v) + outDegree(v)
        new->values[v] = countIn(g, v) + countOut(g, v);
    }
    return *new;
}

//
NodeValues closenessCentrality(Graph g) {
    assert(g != NULL);

    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);

    int nV = numVerticies(g);
    new->noNodes = nV;
    new->values = calloc(nV, sizeof(double));
    assert(new->values != NULL);

    Vertex v;
    double nodereach;
    double nodetotal;

    for (v = 0; v < nV; v++){
        nodereach = countReachable(g, v) - 1;
        nodetotal = numVerticies(g) - 1;

        // according to Wasserman and Faust formula
        new->values[v] = (nodereach * nodereach) / (nodetotal * outWeight(g, v));
        if (nodereach == 0) {
            new->values[v] = 0;
        }
    }
    return *new;
}

NodeValues betweennessCentrality(Graph g) {
    //one sympathy mark please
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);

    for (Vertex v = 0; v < numVerticies(g); v++){
        double value = 0;
        for (Vertex i = 0; i < numVerticies(g); i++) {
            for (Vertex j = 0; j < numVerticies(g); j++) {
                if (i != j && i != v && j != v) {
                    int numPath = countPath(g, i, j);
                    if (!numPath) { continue; }
                    value += (countPathVia(g, i, j, v) / numPath);
                }
            }
        }
        new->values[v] = value;
    }
    return *new;
}

NodeValues betweennessCentralityNormalised(Graph g) {
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);
    //
    NodeValues tmp = betweennessCentrality(g);
    Vertex v;
    for (v = 0; v < new->noNodes; v++) {
        new->values[v] = tmp.values[v] / ((numVerticies(g) - 1) * (numVerticies(g) - 2));
    }
    return *new;
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

/* ******************************
 * Helper functions
 * ****************************** */

/**
  * This helps us to count the number of nodes within the edges arrays.
  * Used to count the outgoing edges and incoming edges.
  * Used in CentralityMeasures.
  */
int countNode(AdjList L) {

    int count = 0;

    adjListNode *curr = L;
    while (curr) {
        count++;
        curr = curr->next;
    }

    return count;
}


/**
  * Returns the amount of nodes in an outgoing edge
  * array from a given vertex. Used for outDegreeCentrality measure.
  *
  */
int countOut(Graph g, Vertex v) {
    return countNode(outIncident(g, v));
}


/**
  * Returns the amount of ndoes in an ingoing edge array
  * from a given vertex. Used for inDegreeCentrality measure.
  *
  */
int countIn(Graph g, Vertex v) {
    return countNode(inIncident(g, v));
}


/**
  * Returns the amount of ndoes can reacheable from a given vertex
  * Used for closenessCentrality measure
  */
int countReachable(Graph g, Vertex v) {
    ShortestPaths sp = dijkstra(g, v);

    int count = 0;
    for (int i = 0; i < numVerticies(g); i++) {
        // dist[i] is not 0 means there exist path from vertex v -> i
        if (sp.dist[i] != 0){
            count++;
        }
    }
    // vertex v can also reach itself, but dist[v] is 0
    count += 1;
    return count;
}

/**
  * Count the total weight of the shortest paths between vertex v
  * to all the other vertexs
  * Used for closenessCentrality measure
  */
double outWeight(Graph g, Vertex v) {

    double totalWeight = 0;
    Vertex w;
    // get shortest path of vertex v
    ShortestPaths sp = dijkstra(g, v);

    for (w = 0; w < numVerticies(g); w++) {
        // go through every index in the dist array of shortest path
        totalWeight += sp.dist[w];
    }
    return totalWeight;
}


// Count how many path exists in graph start from vertex s to Vertex t
double countPath(Graph g, Vertex s, Vertex t) {
    ShortestPaths sp = dijkstra(g, s);
    return countPathHelper(sp, s, t);
}

// helper function to help countPath from vertex s to Vertex t
double countPathHelper(ShortestPaths sp, Vertex s, Vertex t) {

    // Base case of this recursion
    // when we call this function, we wont meet a situation that
    // s == t in the beginning
    // so this if statement will only check if (s == pred->v)
    // which pred = pred[t], if equal, then means Vertex s can get to Vertex t
    if (s == t) {
        return 1;
    }


    double count = 0;
    PredNode *pred = sp.pred[t];
    while (pred) {
        count += countPathHelper(sp, s, pred->v);
        pred = pred->next;
    }
    return count;
}


 //count how many path exist in graph start from src to dest invlove 'v'
double countPathVia(Graph g, Vertex s, Vertex t, Vertex v) {
    ShortestPaths sp = dijkstra(g, s);
    return countPathViaHelper(sp, s, t, v);
}

// helper function to help countPath via Vertex v from vertex s to Vertex t
double countPathViaHelper(ShortestPaths sp, Vertex s, Vertex t, Vertex v) {

    //if (s == t) { return 0; }

    // Base Case of this recursion
    // when we call this function, we wont meet a situation that
    // t == v in the beginning
    // so this if statement will only check if (pred->v == v)
    // which pred = pred[t]
    // if equal, then means Vertex v exist between s and t
    if (t == v) {
        // return the paths number go though Vertex s to v
        return countPathHelper(sp, s, v);
    }

    double count = 0;
    PredNode *pred = sp.pred[t];
    while (pred) {
        // count the path number from vertex s to the pred node of t via vertex v
        count += countPathViaHelper(sp, s, pred->v, v);
        pred = pred->next;
    }
    return count;
}
