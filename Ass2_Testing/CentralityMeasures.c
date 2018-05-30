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

    int nV = numVerticies(g);
    new->noNodes = nV;
    new->values = calloc(nV, sizeof(double));
    assert(new->values != NULL);

    Vertex v;
    for (v = 0; v < nV; v++) {
        new->values[v] = countIn(g, v);
    }

    return *new;
}

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
        new->values[v] = countIn(g, v) + countOut(g, v);
    }
    return *new;
}

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
    // int weight, noOutEdges, noInEdges;
    for (v = 0; v < nV; v++){
        nodereach = countReachable(g, v) - 1;
        nodetotal = numVerticies(g) - 1;
        new->values[v] = (nodereach * (countReachable(g, v) - 1)) / ((numVerticies(g) - 1) * outWeight(g, v));
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
   * array from a given vertex. Used for CentralityMeasures.
   *
   */
 int countOut(Graph g, Vertex v) {
     return countNode(outIncident(g, v));
 }


 /**
   * Returns the amount of ndoes in an ingoing edge array
   * from a given vertex. Used for CnetralityMeasures.
   *
   */
 int countIn(Graph g, Vertex v) {
     return countNode(inIncident(g, v));
 }


 int countReachable(Graph g, Vertex v) {
     ShortestPaths sp = dijkstra(g, v);
     int count = 0;
     for (int i = 0; i < numVerticies(g); i++) {
         if (sp.dist[i] != 0){
             count++;
         }
     }
     count += 1;
     return count;
 }


 double outWeight(Graph g, Vertex v) {
     double totalWeight = 0;
     //getting shortest path
     Vertex w;
     ShortestPaths sp;
     for (w = 0; w < numVerticies(g); w++) {
         sp = dijkstra(g, v);
         totalWeight += sp.dist[w];
     }
     return totalWeight;
 }


 // Count how many path exists in graph start from src to dest
 double countPath(Graph g, Vertex s, Vertex t) {
     ShortestPaths sp = dijkstra(g, s);
     return countPathHelper(sp, s, t);
 }


 double countPathHelper(ShortestPaths sp, Vertex s, Vertex t) {
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


 double countPathViaHelper(ShortestPaths sp, Vertex s, Vertex t, Vertex v) {

     if (s == t) { return 0; }

     if (t == v) { return countPathHelper(sp, s, v); }

     double count = 0;
     PredNode *pred = sp.pred[t];
     while (pred) {
         count += countPathViaHelper(sp, s, pred->v, v);
         pred = pred->next;
     }
     return count;
 }
