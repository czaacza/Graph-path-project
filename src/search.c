#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "search.h"

#define INF 999999

int dijkstra(graph_t graph, int startVertex, int endVertex)
{
  int numOfRows = graph->numOfRows;
  int numOfColumns = graph->numOfColumns;
  double **weight = graph->values;

  int *visited = malloc(sizeof *visited * numOfRows * numOfColumns);
  double *pathLength = malloc(sizeof *pathLength * numOfRows * numOfColumns);
  int *previous = malloc(sizeof *previous * numOfRows * numOfColumns);

  // Initialize list of vertex neighbours
  int *neighboursList = malloc(sizeof *neighboursList * 4);

  int currentVertex = startVertex;
  int currentWeight;
  int nextVertex;

  for (int i = 0; i < numOfRows * numOfColumns; i++)
  {
    visited[i] = 0;
    previous[i] = -1;
    pathLength[i] = INF;
  }

  pathLength[startVertex] = 0;
  visited[startVertex] = 1;

  while (1)
  {
    addNeighbours(graph, neighboursList, currentVertex);
    printf("Neighbours of %d: ", currentVertex);
    for (int i = 0; i < 4; i++)
    {
      printf("%d ", neighboursList[i]);
      printf("pathLength = %g\n", pathLength[neighboursList[i]]);
    }
    printf("\n");

    nextVertex = minPathVertex(visited, numOfRows * numOfColumns, neighboursList, pathLength);
    printf("Next vertex: %d\n", nextVertex);

    visited[nextVertex] = 1;

    if (nextVertex == (currentVertex - numOfColumns))
    {
      currentWeight = weight[currentVertex][0];
    }
    else if (nextVertex == (currentVertex + numOfColumns))
    {
      currentWeight = weight[currentVertex][1];
    }
    else if (nextVertex == currentVertex + 1)
    {
      currentWeight = weight[currentVertex][2];
    }
    else if (nextVertex == currentVertex - 1)
    {
      currentWeight = weight[currentVertex][3];
    }

    currentVertex = nextVertex;

    if (pathLength[currentVertex] + currentWeight < pathLength[nextVertex])
    {
      pathLength[nextVertex] = pathLength[currentVertex] + currentWeight;
      previous[nextVertex] = currentVertex;
    }

    if (areAllVerticesVisited(visited, numOfRows * numOfColumns, pathLength))
    {
      break;
    }
    break;
  }
}

void addNeighbours(graph_t graph, int *neighboursList, int vertex)
{

  for (int i = 0; i < 4; i++)
  {
    neighboursList[i] = -1;
    if (graph->values[vertex][i] > 0)
    {
      switch (i)
      {
      case 0:
        neighboursList[0] = vertex - graph->numOfColumns;
        break;
      case 1:
        neighboursList[1] = vertex + graph->numOfColumns;
        break;
      case 2:
        neighboursList[2] = vertex + 1;
        break;
      case 3:
        neighboursList[3] = vertex - 1;
        break;
      }
    }
  }
}

int isElementPresent(int element, int *array, int arraySize)
{
  for (int i = 0; i < arraySize; i++)
  {
    if (i == element)
    {
      return 1;
    }
  }
  return 0;
}

int minPathVertex(int *visited, int visitedSize, int *neighboursList, double *pathLength)
{
  int minPath = INF;
  int minVertex = -1;

  for (int i = 0; i < 4; i++)
  {
    if (neighboursList[i] != -1 && visited[neighboursList[i]] == 0 && pathLength[neighboursList[i]] <= minPath)
    {
      minPath = pathLength[neighboursList[i]];
      minVertex = neighboursList[i];
    }
  }
  return minVertex;
}

int areAllVerticesVisited(int *visited, int visitedSize, double *pathLength)
{
  int notVisitedVertices = 0;
  int infPathLengths = 0;
  for (int v = 0; v < visitedSize; v++)
  {
    if (visited[v] == 0)
    {
      if (pathLength[v] == INF)
      {
        infPathLengths++;
      }
      notVisitedVertices++;
    }
  }
  if (notVisitedVertices == 0)
  {
    return 1;
  }
  else if (notVisitedVertices > 0)
  {
    return (notVisitedVertices == infPathLengths);
  }
}

int main()
{
  graph_t graph = createGraph();
  loadGraph(graph, "data/danezfilmu");

  dijkstra(graph, 4, 12);
  return 0;
}