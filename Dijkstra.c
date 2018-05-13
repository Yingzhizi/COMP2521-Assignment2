#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Dijkstra.h"
#include "PQ.h"
#include "LList.h"
#define INF 0x7FFFFFFF

// function Dijkstra(Graph, source):
// 2      dist[source] ← 0                                    // Initialization
// 3
// 4      create vertex set Q
// 5
// 6      for each vertex v in Graph:
// 7          if v ≠ source
// 8              dist[v] ← INFINITY                          // Unknown distance from source to v
// 9          prev[v] ← UNDEFINED                         // Predecessor of v
// 10
// 11         Q.add_with_priority(v, dist[v])
// 12
// 13
// 14     while Q is not empty:                              // The main loop
// 15         u ← Q.extract_min()                            // Remove and return best vertex
// 16         for each neighbor v of u:                      // only v that is still in Q
// 17             alt ← dist[u] + length(u, v)
// 18             if alt < dist[v]
// 19                 dist[v] ← alt
// 20                 prev[v] ← u
// 21                 Q.decrease_priority(v, alt)
// 22
// 23     return dist, prev

ShortestPaths dijkstra(Graph g, Vertex source) {
    assert (g != NULL);

    //adjListNode *vertexSet = {};
    PQ vertexSet = newPQ();

    ShortestPaths *sp = malloc(sizeof(struct ShortestPaths));
    assert (sp != NULL);
    sp->src = source;
    sp->noNodes = g->nV;
    for (int i = 0; i < g->nV; i++) {
        sp->dist[i] = INF;
        sp->pred[i] = -1;
        addPQ(vertexSet, g->edges[i]);
    }
    sp->dist[source] = 0;

    while(!PQEmpty(vertexSet)){
        adjListNode *curr = dequeuePQ(vertexSet);
        int i = 0;
        while(i < g->nV){
            if ()
        }
    }
}

void  showShortestPaths(ShortestPaths sp) {
    int i = sp->src;
    //print the dist
    while(i < sp->noNodes){
        printf("%d ", sp->dist[i]);
        i++;
    }
    printf("\n");
    PredNode *curr = sp->pred[sp->src];
    while(curr != NULL){
        printf("%d ", curr->v);
        curr = curr->next;
    }
}

void  freeShortestPaths(ShortestPaths sp) {

    for (int i = 0; i < sp->noNodes; i++) {
        free(sp->dist[i]);
        free(sp->pred[i]);
    }
    free(sp);
}
