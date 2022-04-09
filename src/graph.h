#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct
{
	double **values;
	int numOfRows;
	int numOfColumns;
} * graph_t;

graph_t createGraph();
void loadGraph(graph_t graph, char *fileName);
void saveGraph(graph_t graph, char *outFileName);
void printGraph(graph_t graph);
void initGraphValues(graph_t graph, int numOfRows, int numOfColumns);
void freeGraph(graph_t graph);

#endif