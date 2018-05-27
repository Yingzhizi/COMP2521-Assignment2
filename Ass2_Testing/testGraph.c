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

  Graph g = newGraph(7);
  insertEdge(g,1,2,1);
  insertEdge(g,3,1,1);
  insertEdge(g,2,1,1);
  insertEdge(g,1,3,10);
  insertEdge(g,1,4,60);
  insertEdge(g,1,5,6);
  insertEdge(g,1,6,100);


  showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
