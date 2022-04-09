#include <stdlib.h>

#include "bfs.h"
#include "graph.h"

void enqueue(queue_t queue, int vertex)
{
	queue->elements[++queue->last] = vertex;
}

int dequeue(queue_t queue)
{
	return queue->elements[++queue->first];
}

int isEmpty(queue_t queue)
{
	if (queue->first == queue->last)
		return 1;
	return 0;
}

int checkEdge(int start, int end, graph_t graph)
{
	int numOfColumns = graph->numOfColumns;
	double **values = graph->values;
	if ((end == start - 1 && values[start][0] != 0) ||
		(end == start + 1 && values[start][1] != 0) ||
		(end == start + numOfColumns && values[start][2] != 0) ||
		(end == start - numOfColumns && values[start][3] != 0))
		return 1;
	return 0;
}

int bfs(graph_t graph)
{
	int i;
	int numOfVertices = graph->numOfColumns * graph->numOfRows;

	queue_t queue = malloc(sizeof queue);
	queue->elements = malloc(sizeof(int) * numOfVertices);
	queue->first = queue->last = -1;

	int currentVertex = 0; // zaczynamy od 0
	int *visited = malloc(sizeof(int) * numOfVertices);

	visited[currentVertex] = 1;
	enqueue(queue, currentVertex);

	while (!isEmpty(queue))
	{
		currentVertex = dequeue(queue);
		for (i = 0; i < numOfVertices; i++)
		{
			if (visited[i] == 0 && checkEdge(currentVertex, i, graph))
			{
				visited[i] = 1;
				enqueue(queue, i);
			}
		}
	}
	for (i = 0; i < numOfVertices; i++)
		if (visited[i] == 0)
			return 0;
	return 1;
}