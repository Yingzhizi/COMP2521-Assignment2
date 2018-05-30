#ifndef GRAPH
	#define GRAPH
	#include "Graph.h"
#endif
#include "GraphVis.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	// some very simple code to show you
	// how to use graph vis

  Graph g = newGraph(3);
  insertEdge(g,11,0,5);
  insertEdge(g,11,0,0);
  insertEdge(g,2,0,1);
  showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
