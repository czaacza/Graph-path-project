#include <stdlib.h>
#include <stdio.h>

#include "bfs.h"
#include "graph.h"

static void enqueue(queue_t queue, int vertex)
{
	queue->elements[++queue->last] = vertex;
}

static int dequeue(queue_t queue)
{
	return queue->elements[++queue->first];
}

static int isEmpty(queue_t queue)
{
	if (queue->first == queue->last)
		return 1;
	return 0;
}

static queue_t createQueue(int numOfVertices)
{
	queue_t queue = malloc(sizeof(*queue));
	if (queue == NULL)
	{
		fprintf(stderr, "ERROR: Memory for BFS queue unsuccesfully allocated.\n");
		exit(1);
	}
	queue->elements = malloc(sizeof(int) * numOfVertices);
	if (queue->elements == NULL)
	{
		free(queue);
		fprintf(stderr, "ERROR: Memory for elements in BFS queue unsuccesfully allocated.\n");
		exit(1);
	}
	queue->first = queue->last = -1;
	return queue;
}

int bfs(graph_t graph)
{
	int i, k;
	int numOfVertices = graph->numOfColumns * graph->numOfRows;

	queue_t queue = createQueue(numOfVertices);

	int currentVertex = 0; // zaczynamy od 0
	int *visited = malloc(numOfVertices * sizeof(visited));
	if (visited == NULL)
	{
		fprintf(stderr, "ERROR: Memory for visited vertices in BFS unsuccesfully allocated.\n");
		exit(1);
	}

	visited[currentVertex] = 1;
	enqueue(queue, currentVertex);

	while (!isEmpty(queue))
	{
		currentVertex = dequeue(queue);
		for (i = 0; i < 4; i++)
		{
			k = -1;
			if (i == 0 && graph->values[currentVertex][i] != 0)
				k = currentVertex - graph->numOfColumns;
			if (i == 1 && graph->values[currentVertex][i] != 0)
				k = currentVertex + graph->numOfColumns;
			if (i == 2 && graph->values[currentVertex][i] != 0)
				k = currentVertex + 1;
			if (i == 3 && graph->values[currentVertex][i] != 0)
				k = currentVertex - 1;
			if (visited[k] == 0 && k != -1)
			{
				visited[k] = 1;
				enqueue(queue, k);
			}
		}
	}
	free(queue->elements);
	free(queue);
	for (i = 0; i < numOfVertices; i++)
		if (visited[i] == 0)
		{
			free(visited);
			return 0;
		}
	free(visited);
	return 1;
}