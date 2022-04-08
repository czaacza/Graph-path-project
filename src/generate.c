#include <time.h>
#include <stdlib.h>

#include "generate.h"
#include "graph.h"

double randomInRange(double min, double max)
{
	return min + (rand() / RAND_MAX / (max - min));
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
			weight = randomInRange(minW, maxW);
			graph->values[i][1] = weight;
			graph->values[i + 1][0] = weight; // zamiana indeksów, żeby krawędź była w obie strony
		}
		else if (i % numOfColumns == numOfColumns - 1)
		{ // sprawdza czy wierzchołek jest  w ostatniej kolumnie
			weight = randomInRange(minW, maxW);
			graph->values[i][2] = weight;
			graph->values[i + numOfColumns][3] = weight;
		}
		else
		{ // to się dzieje dla pozostałych wierzchołków
			weight = randomInRange(minW, maxW);
			graph->values[i][1] = weight;
			graph->values[i + 1][0] = weight;
			weight = randomInRange(minW, maxW);
			graph->values[i][2] = weight;
			graph->values[i + numOfColumns][3] = weight;
		}
	}
}