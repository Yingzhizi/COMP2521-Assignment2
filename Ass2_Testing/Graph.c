#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Graph.h"

typedef struct GraphRep {
    int nV;  //number of vertices in the graph
    int nE;  //number of edges in the graph
    AdjList *edges;  //edge array (outgoing edges)
    adjListNode **inedges;  //edge array (ingoing edges)
} GraphRep;


//global functions declaration

// double countOutW(Graph, Vertex);
// int countOut(Graph, Vertex);
// int count(AdjList);

AdjList insertLL(AdjList, int);
AdjList deleteLL(AdjList, int);
bool inLL(AdjList, int);
void freeLL(AdjList);
void showLL(AdjList);
AdjList inIncident(Graph, Vertex);

/**
  * Function is used to make a new graph with
  * noNodes vertices
  *
  */
Graph newGraph(int noNodes) {

    //Make sure noNodes is valid
    assert (noNodes >= 0);

    //create the graph and make sure that it is valid
    Graph g = malloc(sizeof(GraphRep));
    assert (g != NULL);

    //initialise the number of vertex and edges in the graph
    g->nV = noNodes;
    g->nE = 0;

    //create an array of outgoing edges for the graph
    //allocate memory for each row and make sure it is valid
    g->edges = malloc(noNodes * sizeof(adjListNode *));
    assert(g->edges != NULL);

    //create the array of ingoing edges
    //allocate memory for each row and make sure it is valid
    g->inedges = malloc(noNodes * sizeof(adjListNode *));
    assert(g->inedges != NULL);

    //initialise the values in the array of edges
    //since it is a new graph everything is NULL
    for (int i = 0; i < noNodes; i++){
        g->edges[i] = NULL;
        g->inedges[i] = NULL;
    }

    return g;
}

/**
  * This is used to check whether the vertex is valid or not
  *
  */

int validV(Graph g, Vertex v) {

    return (g != NULL && v < g->nV && v >= 0);
}

/**
  * This is used to insert an edge into the graph. It takes in
  * two vertices, a source and a destination, creates an edge
  * and gives it a weight.
  *
  */
void insertEdge(Graph g, Vertex src, Vertex dest, int weight) {

    assert(g != NULL && validV(g, src) && validV(g, dest));

    //Checks to see if the edge exists if it doesn't
    //make an edge and give it a weight. (outgoing edges)
    if (!inLL(g->edges[src], dest)){

        g->edges[src] = insertLL(g->edges[src], dest);
        g->edges[src]->weight = weight;

        //Increment the number of edges
        g->nE++;
    }

    //If an edge from dest to src doesn't exist
    //add it to inedges (ingoing edge)
    if(!inLL(g->inedges[dest], src)){
        g->inedges[dest] = insertLL(g->inedges[dest], src);
    }
}

//wo ai ni

/**
  * This is used to remove an edge from the graph. It takes in a
  * source and a destination and removes the edge formed between
  * it.
  *
  */
void  removeEdge(Graph g, Vertex src, Vertex dest) {

    assert(g != NULL && validV(g, src) && validV(g, dest));

    //Checks to see if the edge exists if it does remove
    //the edge. (outgoing edges)
    if (inLL(g->edges[src], dest)){

        g->edges[src] = deleteLL(g->edges[src], dest);

        //Decrement the number of edges
        g->nE--;
    }

    //Checks to see if the edge exists if it does remove
    //the edge. (ingoing edges)
    if (inLL(g->inedges[dest], src)){
        g->inedges[dest] = deleteLL(g->inedges[dest], src);
    }
}

/**
  * This is used to check if a given source is adjacent
  * to a given destination. Returns true if they are adjacent
  * otherwise false.
  *
  */
bool  adjacent(Graph g, Vertex src, Vertex dest) {

    assert(g != NULL && validV(g, src) && validV(g, dest));
    return (inLL(g->edges[src], dest));
}

/**
  * This returns the number of vertices within the graph.
  *
  */
int  numVerticies(Graph g) {

    assert (g != NULL);
    return g->nV;
}

/**
  * Returns a list of adjacent vertices on outgoing edges
  * from a given vertex.
  *
  */
AdjList outIncident(Graph g, Vertex v) {

    assert(g != NULL && validV(g, v));
   //AdjList L = g->edges[v];

    return g->edges[v];
}

/**
  * Returns the amount of nodes in an outgoing edge
  * array from a given vertex. Used for CentralityMeasures.
  *
  */
// int countOut(Graph g, Vertex v) {
//
//     assert(g != NULL && validV(g, v));
//     return count(g->edges[v]);
// }

/**
  * Returns the amount of ndoes in an ingoing edge array
  * from a given vertex. Used for CnetralityMeasures.
  *
  */

// int countIn(Graph g, Vertex v) {
//
//     assert(g != NULL && validV(g, v));
//     return count(g->inedges[v]);
// }

/**
  * Need to fix this function before commenting on it.
  *
  */
// double countOutW(Graph g, Vertex v){
//     assert(g != NULL && validV(g, v));
//     double totalWeight = 0;
//     ShortestPaths *sp = malloc(sizeof(ShortestPaths));
//     assert(sp != NULL);
//     //getting shortest path
//     sp = dijkstra(g, v);
//     //weight will change depending on where we are
//     for(int j = 0; j < sp->noNodes; j++){
//         totalWeight += sp->dist[j];
//     }
//
//     return totalWeight;
// }

/**
  * Returns a list of vertices on incoming edges
  * from a given vertex.
  *
  */
AdjList inIncident(Graph g, Vertex v) {

    assert(g != NULL && validV(g, v));
    return (g->inedges[v]);
}

/**
  * This is used to show what the graph looks like.
  * The function is displays information about the graph as well.
  * Displays information in this form:
  *     - Number of vertices and edges
  *     - Then edges in this form src - list of connecting edges to
  *       that source
  *
  */
void showGraph(Graph g) {

    assert (g != NULL);

    //shows number of vertices and edges
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);

    //displays the edges within the graph
    int i;
    for (i = 0; i < g->nV; i++) {
        //displays the source node
        printf("%d - ", i);
        //displays all nodes that forms edges towards the source node
        showLL(g->edges[i]);
    }
}

/**
  * Frees everything in the graph
  *
  */
void freeGraph(Graph g) {

    assert(g != NULL);

    //goes through every vertice in the graph and frees everything
    int i;
    for (i = 0; i < g->nV; i++)
        freeLL(g->edges[i]);
    free(g->edges);
    free(g);
}


//Helper functions - stupid adjacency list graph
//Taken from the lecture exercises

/**
  * This makes a node for adding it into a edge list.
  *
  */
adjListNode *makeNode(int n) {

    //make a node and make sure it is valid
    adjListNode *new = malloc(sizeof(adjListNode));
    assert(new != NULL);

    //initialise the node's components
    new->w = n;
    new->weight = 0;
    new->next = NULL;

    return new;
}

/**
  * Used to help insert the destination node into a source node
  * in the edge list.
  * This forms an edge between a source and destination.
  *
  */
AdjList insertLL(AdjList L, int n) {

    //if edge already exist don't do anything
    if (inLL(L, n))
        return L;

    // add new node at the beginning
    adjListNode *new = makeNode(n);
    new->next = L;

    return new;
}

/**
  * Used to help remove the destination node from a source node
  * in the edge list.
  * This removes an edge between a source and destination.
  *
  */
AdjList deleteLL(AdjList L, int n) {

    //If L is NULL just return it
    if (L == NULL)
        return L;

    //If we are at the node to be deleted it and
    //return the new list.
    if (L->w == n)
        return L->next;

    //Try and find the node we need to delete using
    //recursion.
    L->next = deleteLL(L->next, n);

    return L;
}

/**
  * Checks to see if a node is already in the edge list.
  * Returns false if edge list is NULL or node isn't in the edge
  * list. Otherwise return true.
  *
  */
bool inLL(AdjList L, int n) {

    //If L is NULL return false
    if (L == NULL)
        return false;

    //If the node is in the list return true
    if (L->w == n)
        return true;

    //Try and find the node using recursion and return true
    //or false based on base case.
    return inLL(L->next, n);
}

/**
  * This helps us to count the number of nodes within the edges arrays.
  * Used to count the outgoing edges and incoming edges. Used in CentralityMeasures.
  *
  */
// int count(AdjList L) {
//
//     int c = 0;
//
//     //counts number of nodes in edge list.
//     while (L != NULL) {
//         c++;
//         L = L->next;
//     }
//
//     return c;
// }

/**
  * Displays the destination nodes in linked to a source node.
  * Used in showGraph.
  *
  */
void showLL(AdjList L) {

    //if L is NULL print new line
    if (L == NULL)
       putchar('\n');
    //else print the nodes in the list
    else {
       printf("%d ", L->w);
       showLL(L->next);
    }
}

/**
  * Free the edge list.
  *
  */
void freeLL(AdjList L) {

    if (L != NULL) {
       freeLL(L->next);
       free(L);
    }
}
