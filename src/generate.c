#include "generate.h"
#include "graph.h"

double randomInRange(double min, double max)
{
	// ...
}

int genGraph(graph_t graph, double chance, double minW, double maxW)
{
	int i, j;
	int numOfColumns = graph->numOfColumns;
	int numOfRows = graph->numOfRows;

	for (i = 0; i < numOfColumns * numOfRows - 1; i++)
	{
		if (i >= numOfColumns * (numOfRows - 1))
		{ // sprawdza czy wierzchołek jest w ostatnim wierszu
			graph->values[i][1] = randomInRange(minW, maxW);
			graph->values[i + 1][0] = randomInRange(minW, maxW); // zamiana indeksów, żeby krawędź była w obie strony
		}
		else if (i % numOfColumns == numOfColumns - 1)
		{ // sprawdza czy wierzchołek jest  w ostatniej kolumnie
			graph->values[i][2] = randomInRange(minW, maxW);
			graph->values[i + numOfColumns][3] = randomInRange(minW, maxW);
		}
		else
		{ // to się dzieje dla pozostałych wierzchołków
			graph->values[i][1] = randomInRange(minW, maxW);
			graph->values[i + 1][0] = randomInRange(minW, maxW);
			graph->values[i][2] = randomInRange(minW, maxW);
			graph->values[i + numOfColumns][3] = randomInRange(minW, maxW);
		}
	}
}