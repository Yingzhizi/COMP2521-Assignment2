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
//sigma s_t
//correct
double countPath(Graph g, Vertex s, Vertex t) {
    //checkValid g and src and dest
    ShortestPaths sp = dijkstra(g, s);
    double count = 0;
    PredNode *curr;
    if (sp.dist[t] != 0 && sp.pred[t] != NULL) {
        curr = sp.pred[t];
        while(curr != NULL) {
            count++;
            curr = curr->next;
        }
    }
    return count;
}

//count how many path exist in graph start from src to dest invlove 'v'
//sigma s_t (v)
//we set that s != t, t != v, s != v
//I think it's works now
double countBetween(Graph g, Vertex s, Vertex t, Vertex v) {
    ShortestPaths sp = dijkstra(g, s);
    double count = 0;
    PredNode *curr;
    //printf("countBeforeif: %d\n", count);
    //fix the stupid not equal check later
    if (sp.dist[t] != 0 && sp.pred[t] != NULL && (t != v && t != s && s != v && s != t && v != s && v != t)) {
        //printf("I'm here\n");
        curr = sp.pred[t];
        while(curr != NULL) {
            if (curr->v == v) {
                count++;
            } else {
                PredNode *tmp = sp.pred[curr->v];
                while (tmp != NULL) {
                    if (tmp->v == v) {
                        count++;
                        tmp = tmp->next;
                    } else {
                        tmp = sp.pred[tmp->v];
                    }
                }
            }
            curr = curr->next;
        }
    }
    return count;
}

// int inPath(Vertex src, Vertex dest) {
//     //return 1 if in
//     //return 0 if not
// }

NodeValues betweennessCentrality(Graph g) {
    //one sympathy mark please
    assert(g != NULL);
    NodeValues *new = malloc(sizeof(NodeValues));
    assert(new != NULL);
    new->noNodes = numVerticies(g);
    new->values = calloc(numVerticies(g), sizeof(double));
    assert(new->values != NULL);
    for (int v = 0; v < numVerticies(g); v++){
        double value = 0;
        int i = 0;
        while (i < numVerticies(g)) {
            Vertex j = 0;
            while (j < numVerticies(g)) {
                if (i != j && i != v && j != v) {
                    if(countPath(g, i ,j) != 0){
                        value += countBetween(g, i, j, v) / countPath(g, i, j);
                    }
                }
                j++;
            }
            i++;
        }
        new->values[v] = value;

    }

    return *new;
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
