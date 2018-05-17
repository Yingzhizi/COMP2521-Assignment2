#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "LList.h"


typedef struct GraphRep {
    int nV;
    int nE;
    adjListNode **edges;
    adjListNode **inedges;
} GraphRep;

/**
  *Function is used to make a new graph
  *
  */
Graph newGraph(int noNodes) {

    //check to make sure the noNodes is valid
    assert (noNodes >= 0);

    //create a graph and make sure that it is valid
    Graph g = malloc(sizeof(GraphRep));
    assert (g != NULL);

    //initialise the things in the struct
    g->nV = noNodes;
    g->nE = 0;

    //create the array of edges and check to make sure it is valid
    g->edges = malloc(noNodes * sizeof(adjListNode));
    assert(g->edges != NULL);

    //create the array of incident edges
    g->inedges = malloc(noNode * sizeof(adjListNode));
    assert(g->inedges != NULL);

    //fill the edge array up
    for (int i = 0; i < noNodes; i++)
        g->edges[i] = NULL;
    return g;
}

int validV(Graph g, Vertex v) {
    return (g != NULL && v < g->nV && v >= 0);
}

void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {
    assert(g != NULL && validV(g, src) && validV(g, dest));
    //if the edge is not in the graph
    if (!inList(g->edges[src], dest)) {
        //insert to out-incident
        g->edges[src] = insertLL(g->edges[src], dest);
        g->edges[src].weight = weight;

        //insert to in-incident
        g->inedges[dest] = insertLL(g->inedges[dest], src);
    }
    g->nE++;
}
//wo ai ni
void  removeEdge(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL && validV(g, src) && validV(g, dest));
    if (inList(g->edges[src], dest)) {
        g->edges[src] = removeLL(g->edges[src], dest);
    }
    g->nE--;
}

bool  adjacent(Graph g, Vertex src, Vertex dest) {
    assert(g != NULL && validV(g, src) && validV(g, dest));
    return (inList(g->edges[src], dest));
}

int  numVerticies(Graph g) {
    assert (g != NULL);
    return g->nV;
}

/*
 * Returns a list of adjacent vertices
 * on outgoing edges from a given vertex.
**/
AdjList outIncident(Graph g, Vertex v) {
    assert(g != NULL && validV(g, v));
    return (g->edges[v]);
}
/*

 * Returns a list of adjacent vertices
 * on incoming edges from a given vertex.
**/
AdjList inIncident(Graph g, Vertex v) {
    assert(g != NULL && validV(g, v));
    return (g->inedges[v]);
}


void  showGraph(Graph g) {
    assert (g != NULL);
    int i;
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++) {
       printf("%d - ", i);
       showLL(g->edges[i]);
    }
}

void  freeGraph(Graph g) {
    assert(g != NULL);
    int i;
    for (i = 0; i < g->nV; i++)
       freeLL(g->edges[i]);
    free(g->edges);
    free(g);
}
