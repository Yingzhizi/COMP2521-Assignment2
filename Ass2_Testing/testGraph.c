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

  Graph g = newGraph(20);
  insertEdge(g,1,2,1);
  insertEdge(g,2,1,10);
  insertEdge(g,4,2,60);
  insertEdge(g,5,2,6);
  insertEdge(g,6,1,100);
  insertEdge(g,7,2,24);
  insertEdge(g,8,2,54);
  insertEdge(g,9,2,86);
  insertEdge(g,10,3,39);
  insertEdge(g,11,10,324);
  insertEdge(g,12,14,12);
  insertEdge(g,13,19,13);
  insertEdge(g,14,17,1);
  insertEdge(g,15,15,6);
  insertEdge(g,16,16,99);
  insertEdge(g,17, 15,4);
  insertEdge(g,18,16,5);
  insertEdge(g,19,2,7);
  removeEdge(g,1,2);
  removeEdge(g,2,1);
  removeEdge(g,4,2);
  removeEdge(g,5,2);
  removeEdge(g,6,1);
  removeEdge(g,7,2);
  removeEdge(g,8,2);
  removeEdge(g,9,2);
  removeEdge(g,10,3);
  removeEdge(g,11,10);
  removeEdge(g,12,14);
  removeEdge(g,13,19);
  removeEdge(g,14,17);
  removeEdge(g,15,15);
  removeEdge(g,16,16);
  removeEdge(g,17, 15);
  removeEdge(g,18,16);
  removeEdge(g,19,2);

  showGraph(g);

	// draws the graph
  graphVis(g, DEFAULT);
	return EXIT_SUCCESS;
}
