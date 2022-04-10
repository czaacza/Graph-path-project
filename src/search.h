#ifndef _SEARCH_H_
#define _SEARCH_H_

typedef struct returnValues
{
  int *path;
  int numOfVisitedVertices;
  double length;
} * returnValues_t;

returnValues_t dijkstra(graph_t graph, int startVertex, int endVertex);
void addNeighbours(graph_t graph, int *neighboursList, int vertex);
int isElementPresent(int element, int *array, int arraySize);
int minPathVertex(int *visited, int numOfVertices, double *pathLength);
int areAllVerticesVisited(int *visited, int visitedSize, double *pathLength);
double findWeight(int currentVertex, int nextVertex, double **weight, int numOfColumns);
void reverse(int arr[], int n);
void printReturnedValues(FILE *out, char *outFileName, returnValues_t returnedValues, int startVertex, int endVertex);

#endif