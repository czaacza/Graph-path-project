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
int loadGraph(graph_t graph, char *fileName);

#endif