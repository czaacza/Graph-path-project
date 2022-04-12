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
#endif