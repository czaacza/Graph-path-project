#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph_t createGraph()
{
	graph_t newGraph = malloc(sizeof *newGraph);
	if (newGraph == NULL)
	{
		fprintf(stderr, "ERROR: Memory for graph unsuccesfully allocated.\n");
		exit(1);
	}

	return newGraph;
}

void initGraphValues(graph_t graph, int numOfRows, int numOfColumns)
{

	graph->values = malloc(sizeof(double *) * numOfRows * numOfColumns);

	for (int i = 0; i < numOfRows * numOfColumns; i++)
	{
		graph->values[i] = malloc(4 * sizeof(double));
	}

	if (graph->values == NULL)
	{
		fprintf(stderr, "ERROR: Memory for vertices unsuccesfully allocated.\n");
		exit(1);
	}
}

void printGraph(graph_t graph)
{
	for (int i = 0; i < graph->numOfRows * graph->numOfColumns; i++)
	{
		printf("W.%d ", i);
		printf("values = [ ");
		for (int j = 0; j < 4; j++)
		{
			printf("%g ", graph->values[i][j]);
		}
		printf("]\n");
	}
}

void freeGraph(graph_t graph)
{
	int i;
	for (i = 0; i < graph->numOfColumns * graph->numOfRows; i++)
	{
		free(graph->values[i]);
	}

	free(graph->values);
	free(graph);
}