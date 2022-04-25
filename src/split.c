#include <stdio.h>
#include <stdlib.h>

#include "search.h"
#include "graph.h"
#include "split.h"

void removeEdge(graph_t graph, int i, int j)
{
	int numOfColumns = graph->numOfColumns;
	graph->values[i][j] = 0;
	switch (j)
	{
	case 0:
		graph->values[i - numOfColumns][1] = 0;
		break;
	case 1:
		graph->values[i + numOfColumns][0] = 0;
		break;
	case 2:
		graph->values[i + 1][3] = 0;
		break;
	case 3:
		graph->values[i - 1][2] = 0;
		break;
	default:
		break;
	}
}

void split(graph_t graph, int splitStart, int splitEnd)
{

	returnValues_t pathData = malloc(sizeof *pathData);
	if (pathData == NULL)
	{
		fprintf(stderr, "ERROR: Memory for the graph split data unsuccesfully allocated.\n");
		exit(1);
	}
	dijkstra(pathData, graph, splitStart, splitEnd);

	int *path = pathData->path;
	int length = pathData->numOfVisitedVertices;
	int numOfColumns = graph->numOfColumns;
	int numOfRows = graph->numOfRows;
	int i;
	for (i = 0; i < length; i++)
	{
		if (path[i] == numOfColumns * numOfRows - 1)
		{ // vertex is in bottom right corner
			continue;
		}
		else if (path[i] % numOfColumns == numOfColumns - 1)
		{ // vertex is in the last column
			removeEdge(graph, path[i], 1);
		}
		else if (path[i] > numOfColumns * (numOfRows - 1))
		{ // vertex is in the last row
			removeEdge(graph, path[i], 2);
		}
		else
		{
			removeEdge(graph, path[i], 2);
			removeEdge(graph, path[i], 1);
		}
	}
	free(pathData->path);
	free(pathData);
}