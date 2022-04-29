#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "graph.h"

typedef struct returnValues
{
	int *path;
	int numOfVisitedVertices;
	double length;
} * returnValues_t;

void dijkstra(returnValues_t returnValues, graph_t graph, int startVertex, int endVertex);
void addNeighbours(graph_t graph, int *neighboursList, int vertex);
int minPathVertex(int *visited, int numOfVertices, double *pathLength);
int areAllVerticesVisited(int *visited, int visitedSize, double *pathLength);
double findWeight(int currentVertex, int nextVertex, double **weight, int numOfColumns);
void reverse(int arr[], int n);
void printReturnedValues(FILE *out, char *outFileName, returnValues_t returnedValues, int startVertex, int endVertex);

#endif