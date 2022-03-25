#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i, j;
	FILE *out = fopen(argv[1], "w");

	int c = 4; // liczba kolumn
	int r = 3; // liczba wierdszy

	int **graph = malloc(c * r * sizeof *graph);
	for (i = 0; i < r * c; i++)
		graph[i] = malloc(c * r * sizeof graph);

	for (i = 0; i < c * r; i++)
	{
		if (i % c == c - 1 && i >= (c - 1) * r)
		{ // sprawdza czy wierzchołek jest w prawym dolnym rogu grafu
			break;
		}
		if (i >= (c - 1) * r)
		{ // sprawdza czy wierzchołek jest w ostatnim wierszu
			graph[i][i + 1] = 5;
		}
		else if (i % c == c - 1)
		{ // sprawdza czy wierzchołek jest  w ostatniej kolumnie
			graph[i][i + c] = 5;
		}
		else
		{
			graph[i][i + 1] = 5; // to się dzieje dla pozostałych wierzchołków
			graph[i][i + c] = 5;
		}
	}

	fprintf(out, "%d %d", r, c);
	for (i = 0; i < c * r; i++)
	{
		fprintf(out, "\n");
		for (j = 0; j < c * r; j++)
		{
			if (graph[i][j] == 5)
				fprintf(out, "%d :waga ", j);
			else if (graph[j][i] == 5) // zamieniamy indeksy żeby połączenie było w 2 strony
				fprintf(out, "%d :waga ", j);
		}
	}

	return 0;
}