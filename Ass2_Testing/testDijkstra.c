#include "Dijkstra.h"
#include "GraphVis.h"
#include <stdlib.h>
#include <stdio.h>

Graph readGraph(char* file) {
	// ugly count
	FILE * f = fopen(file , "r");
	if(!f){
		fprintf(stderr, "ERROR READING FILE %s\n", file);
		return NULL;
	}
	int lines = 0;
	char ch = 0;
	while(!feof(f)){ch = fgetc(f); if(ch == '\n')lines++;}
	fclose(f);

	//ugly parse
	f = fopen(file , "r");
	if(!f){
		fprintf(stderr, "ERROR READING FILE %s\n", file);
		return NULL;
	}
	Graph g = newGraph(lines);
	int a=0;
	int b=0;
	int c=0;
	int i = 0;
	while(i < lines) {
		fscanf(f, "%d,", &a);
		fscanf(f, "%d,", &b);
		fscanf(f, "%d", &c);
		insertEdge(g,a,b,c);
		i++;
	}
	fclose(f);
	return g;
}

void displayShortestPathsStruct(ShortestPaths sps){
	int i = 0;
	printf("Node %d\n",sps.src);
	printf("  Distance\n");
	for (i = 0; i < sps.noNodes; i++) {
			if(i == sps.src)
	    	printf("    %d : X\n",i);
			else
				printf("    %d : %d\n",i,sps.dist[i]);
	}
	printf("  Preds\n");
	for (i = 0; i < sps.noNodes; i++) {
		printf("    %d : ",i);
		PredNode* curr = sps.pred[i];
		while(curr!=NULL) {
			printf("[%d]->",curr->v);
			curr = curr->next;
		}
		printf("NULL\n");
	}
}

int main(int argc, char* argv[]){
	if(argc < 2) {
		printf("Usage: ./testDijkstra [file]\n");
		return EXIT_FAILURE;
	}
  Graph g = readGraph(argv[1]);
  int i;
  for(i=0; i<numVerticies(g); i++) {
    ShortestPaths paths = dijkstra(g,i);
    displayShortestPathsStruct(paths);
    freeShortestPaths(paths);
  }
}
