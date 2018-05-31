#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "LanceWilliamsHAC.h"

/*
 * Finds Dendrogram using Lance-Williams algorithm (as discussed in the specs)
   for the given graph g and the specified method for agglomerative clustering.
   Method value 1 represents 'Single linkage', and 2 represents 'Complete linkage'.
   For this assignment, you only need to implement the above two methods.

   The function returns 'Dendrogram' structure (binary tree) with the required information.
 *
 */
Dendrogram LanceWilliamsHAC(Graph g, int method);


void freeDendrogram(Dendrogram d);
