#ifndef BFS_H
#define BFS_H

#include "graph.h"

typedef struct
{
	int first;
	int last;
	int *elements;
} * queue_t;

int bfs(graph_t graph);
void enqueue(queue_t queue, int currentVertex);
int isEmpty(queue_t queue);
int dequeue(queue_t queue);
int checkEdge(int start, int end, graph_t graph);
#endif