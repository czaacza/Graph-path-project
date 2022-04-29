#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "generate.h"
#include "graph.h"

static double randomInRange(double min, double max)
{
	return min + (rand() / (RAND_MAX / (max - min)));
}

int genGraph(graph_t graph, double chance, double minW, double maxW)
{
	int i, j;
	srand(time(NULL));
	int numOfColumns = graph->numOfColumns;
	int numOfRows = graph->numOfRows;
	double weight;
	for (i = 0; i < numOfColumns * numOfRows - 1; i++)
	{
		if (i >= numOfColumns * (numOfRows - 1))
		{ // sprawdza czy wierzchołek jest w ostatnim wierszu
			if (chance < randomInRange(0, 100))
			{
				weight = randomInRange(minW, maxW);
			}
			else
			{
				weight = 0;
			}
			graph->values[i][2] = weight;
			graph->values[i + 1][3] = weight; // zamiana indeksów, żeby krawędź była w obie strony
		}
		else if (i % numOfColumns == numOfColumns - 1)
		{ // sprawdza czy wierzchołek jest  w ostatniej kolumnie
			if (chance < randomInRange(0, 100))
			{
				weight = randomInRange(minW, maxW);
			}
			else
			{
				weight = 0;
			}
			graph->values[i][1] = weight;
			graph->values[i + numOfColumns][0] = weight;
		}
		else
		{ // to się dzieje dla pozostałych wierzchołków
			if (chance < randomInRange(0, 100))
			{
				weight = randomInRange(minW, maxW);
			}
			else
			{
				weight = 0;
			}
			graph->values[i][2] = weight;
			graph->values[i + 1][3] = weight;
			if (chance < randomInRange(0, 100))
			{
				weight = randomInRange(minW, maxW);
			}
			else
			{
				weight = 0;
			}
			graph->values[i][1] = weight;
			graph->values[i + numOfColumns][0] = weight;
		}
	}
}