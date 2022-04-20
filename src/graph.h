#ifndef GRAPH_H
#define GRAPH_H

typedef struct
{
	double **values;
	int numOfRows;
	int numOfColumns;
} * graph_t;

graph_t createGraph();
void printGraph(graph_t graph);
void initGraphValues(graph_t graph, int numOfRows, int numOfColumns);
void freeGraph(graph_t graph);

#endif