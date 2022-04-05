#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct
{
	double **vertices;
	int numOfColumns;
	int numOfRows;
} * graph_t;

#endif