#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "search.h"

#define INF 999999

returnValues_t dijkstra(graph_t graph, int startVertex, int endVertex)
{
  returnValues_t returnValues = malloc(sizeof *returnValues);
  returnValues->length = -1;
  returnValues->path = NULL;
  returnValues->numOfVisitedVertices = -1;

  int numOfRows = graph->numOfRows;
  int numOfColumns = graph->numOfColumns;
  double **weight = graph->values;

  int *visited = malloc(sizeof *visited * numOfRows * numOfColumns);
  double *pathLength = malloc(sizeof *pathLength * numOfRows * numOfColumns);
  int *previous = malloc(sizeof *previous * numOfRows * numOfColumns);

  int *neighboursList = malloc(sizeof *neighboursList * 4);

  int currentVertex;
  double currentWeight;
  int nextVertex;

  for (int i = 0; i < numOfRows * numOfColumns; i++)
  {
    visited[i] = 0;
    previous[i] = -1;
    pathLength[i] = INF;
  }

  pathLength[startVertex] = 0;

  while (1)
  {
    currentVertex = minPathVertex(visited, numOfRows * numOfColumns, pathLength);
    visited[currentVertex] = 1;

    addNeighbours(graph, neighboursList, currentVertex);

    for (int v = 0; v < 4; v++)
    {
      if (neighboursList[v] != -1 && visited[neighboursList[v]] == 0)
      {
        nextVertex = neighboursList[v];
        currentWeight = findWeight(currentVertex, nextVertex, weight, numOfColumns);

        if (pathLength[currentVertex] + currentWeight < pathLength[nextVertex])
        {
          pathLength[nextVertex] = pathLength[currentVertex] + currentWeight;
          previous[nextVertex] = currentVertex;
        }

        // printf("Current vertex: %d\n", currentVertex);
        // printf("Next vertex: %d\n", nextVertex);
        // printf("CurrentWeight: %g\n", currentWeight);
        // printf("pathLength[nextVertex] = %g\n", pathLength[nextVertex]);
        // printf("previous[nextVertex] = %d\n", previous[nextVertex]);
        // printf("\n");
      }
    }

    if (areAllVerticesVisited(visited, numOfRows * numOfColumns, pathLength) || currentVertex == endVertex)
    {
      // printf("pathLength[]: ");
      // for (int i = 0; i < numOfRows * numOfColumns; i++)
      // {
      //   printf("%g ", pathLength[i]);
      // }
      // printf("\nvisited[]: ");
      // for (int i = 0; i < numOfRows * numOfColumns; i++)
      // {
      //   printf("%d ", visited[i]);
      // }
      // printf("\nprevious[]: ");
      // for (int i = 0; i < numOfRows * numOfColumns; i++)
      // {
      //   printf("%d ", previous[i]);
      // }
      // printf("\n");

      if (pathLength[endVertex] == INF)
      {
        break;
      }

      int iterator = endVertex;
      int *endVertexPath = malloc(1 * sizeof(int));
      int *tempArray = malloc(1 * sizeof(int));
      int numOfElements = 0;

      while (iterator != startVertex)
      {
        iterator = previous[iterator];
        endVertexPath[0] = endVertex;
        endVertexPath[numOfElements] = iterator;
        numOfElements++;
        tempArray = realloc(endVertexPath, numOfElements * sizeof(int));
        if (tempArray == NULL)
        {
          fprintf(stderr, "ERROR: Memory for endVertexPath wrongly allocated.\n");
          exit(1);
        }
        endVertexPath = tempArray;
      }
      reverse(endVertexPath, numOfElements);

      returnValues->length = pathLength[endVertex];
      returnValues->path = endVertexPath;
      returnValues->numOfVisitedVertices = numOfElements;

      break;
    }
  }
  return returnValues;
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

int minPathVertex(int *visited, int numOfVertices, double *pathLength)
{
  int minPath = INF;
  int minVertex = -1;

  for (int v = 0; v < numOfVertices; v++)
  {
    if (visited[v] == 0 && pathLength[v] <= minPath)
    {
      minPath = pathLength[v];
      minVertex = v;
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

double findWeight(int currentVertex, int nextVertex, double **weight, int numOfColumns)
{

  if (nextVertex == (currentVertex - numOfColumns))
  {
    return weight[currentVertex][0];
  }
  else if (nextVertex == (currentVertex + numOfColumns))
  {
    return weight[currentVertex][1];
  }
  else if (nextVertex == currentVertex + 1)
  {
    return weight[currentVertex][2];
  }
  else if (nextVertex == currentVertex - 1)
  {
    return weight[currentVertex][3];
  }
  else
  {
    fprintf(stderr, "ERROR: %d is not a neighbour of %d ", nextVertex, currentVertex);
    exit(99);
  }
}

void reverse(int arr[], int n)
{
  for (int low = 0, high = n - 1; low < high; low++, high--)
  {
    int temp = arr[low];
    arr[low] = arr[high];
    arr[high] = temp;
  }
}

void printReturnedValues(FILE *out, char *outFileName, returnValues_t returnedValues, int startVertex, int endVertex)
{
  int *path = returnedValues->path;
  int numOfVisitedVertices = returnedValues->numOfVisitedVertices;
  double length = returnedValues->length;

  fprintf(out, "\nStarting vertex: %d\n", startVertex);
  fprintf(out, "Ending vertex: %d\n", endVertex);

  if (length == -1 || path == NULL || numOfVisitedVertices == -1)
  {
    fprintf(out, "\nThere is no connection between vertices %d and %d.\n", startVertex, endVertex);
    return;
  }

  if (out != stdout)
  {
    fprintf(stdout, "Succesfully found the shortest path.\n");
    fprintf(stdout, "Search information printed to %s\n", outFileName);
  }

  fprintf(out, "\nShortest path between %d and %d: %d ", startVertex, endVertex, path[0]);
  for (int i = 1; i < numOfVisitedVertices; i++)
  {
    fprintf(out, "-> %d ", path[i]);
  }
  fprintf(out, "\nLength of the shortest path: %g\n", length);
}