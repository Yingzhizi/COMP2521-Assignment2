// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include "Graph.c"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INF 0x7FFFFFFF

void set_pred(ShortestPaths, Vertex, Vertex, Vertex);
void set_equal_pred(ShortestPaths,Vertex, Vertex, Vertex);

ShortestPaths dijkstra(Graph g, Vertex source) {
assert (g != NULL);

    int nV = numVerticies(g);
    //adjListNode *vertexSet = {};

    //int seen[g->nV];
    ShortestPaths sp;
    sp.src = source;
    sp.noNodes = nV;
    sp.dist = malloc(nV *sizeof(int));
    assert(sp.dist != NULL);
    // sp->src = source;

	sp.pred = malloc(nV * sizeof(PredNode *));
	assert(sp.pred != NULL);

    int seen[nV];

    for (int i = 0; i < nV; i++) {
        sp.dist[i] = INF;
        sp.pred[i] = NULL;
        seen[i] = -1;
        // seen[i] = 0;
		// ItemPQ *new = malloc(sizeof(ItemPQ));
		// new->key = edge->w;
		// new->value = edge->weight;
  //       addPQ(vertexSet, *new);
    }
    sp.dist[source] = 0;

    PQ vertexSet = newPQ();

    ItemPQ new;
    new.key = source;
    new.value = sp.dist[source];

    addPQ(vertexSet, new);

    while(!PQEmpty(vertexSet)){
        ItemPQ curr = dequeuePQ(vertexSet);

        if(seen[curr.key] != -1) continue;
        seen[curr.key] = 1;
        AdjList edge = outIncident(g, curr.key);
        while(edge != NULL){
            if(sp.dist[curr.key] + edge->weight <= sp.dist[edge->w]){
                if(sp.dist[curr.key] + edge->weight == sp.dist[edge->w]){
                    sp.dist[edge->w] = sp.dist[curr.key] + edge->weight;
                    set_equal_pred(sp, edge->w, curr.key, source);
                } else {
                    sp.dist[edge->w] = sp.dist[curr.key] + edge->weight;
                    set_pred(sp, edge->w, curr.key, source);
                }
                new.key = edge->w;
                new.value = edge->weight;
                addPQ(vertexSet, new);
            }
            edge = edge->next;
        }
    }


    // int count = 0;
    // //if we found that a node is isolated, we need to get rid of this from the shortest path
    // int i;
    // for(i = 0; i < nV; i++){
    //     if(sp.dist[i] == INF && sp.pred[sp.dist[i].w] == NULL && i != nV - 1){
    //         sp.dist[i] = 0;
    //         count++;
    //     }
    // }
    // if (sp.dist[i] == INF) {
    //     sp.dist[i] = 0;
    // }
    // sp.noNodes = nV - count;

    int i;
    for(i = 0; i < nV; i++){
        if(sp.dist[i] == INF && sp.pred[sp.dist[i].w] == NULL && i != nV - 1){
            sp.dist[i] = 0;
            count++;
        }
    }

    return sp;

}
//sets pred node
void set_pred(ShortestPaths path,Vertex w, Vertex v, Vertex src){
  path.pred[w] = malloc(sizeof(PredNode));
  path.pred[w]->v = v;
  path.pred[w]->next = NULL;
}

//function to see if a string of paths is better than another path which may be direct
void set_equal_pred(ShortestPaths path,Vertex w, Vertex v, Vertex src){
  PredNode * new = malloc(sizeof(PredNode));
  new->v = v;
  new->next = NULL;
  PredNode * curr = path.pred[w];
  while(path.pred[w]->next!=NULL){
    path.pred[w] = path.pred[w]->next;
  }
  path.pred[w]->next = new;
  path.pred[w] = curr;
}

void showShortestPaths(ShortestPaths sp) {
    int i = sp.src;
    //print the dist
    while(i < sp.noNodes){
        printf("%d ", sp.dist[i]);
        i++;
    }
    printf("\n");
    PredNode *curr = sp.pred[sp.src];
    while(curr != NULL){
        printf("%d ", curr->v);
        curr = curr->next;
    }
}


void  freeShortestPaths(ShortestPaths sp) {

    free(sp.pred);
    free(sp.dist);
}

// int countIsolated(Graph g) {
//     int nV = numVerticies(g);
//
//     int buff[nV];
//     for(int i = 0; i < nV; i++) {
//         buff[i] = 0;
//     }
//
//     for (int i = 0; i < nV; i++) {
//         AdjList curr = g->edges[i];
//         while (curr != NULL) {
//             buff[curr->w] = 1;
//             curr = curr->next;
//         }
//     }
//
//     int count = 0;
//     for (int i = 0; i < nV; i++) {
//         if (buff[i] == 0) {
//             count++;
//         }
//     }
//
//     return count;
// }
