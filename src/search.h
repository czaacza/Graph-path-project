#ifndef _SEARCH_H_
#define _SEARCH_H_

typedef struct returnValues
{
  int *path;
  int length;
} returnValues_t;

int dijkstra(graph_t graph, int startVertex, int endVertex);
int addNeighbours(graph_t graph, int *neighboursList, int vertex);
int isElementPresent(int element, int *array, int arraySize);
int minPathVertex(int *visited, int visitedSize, int *neighboursList, double *pathLength);
int areAllVerticesVisited(int *visited, int visitedSize, double *pathLength);

#endif