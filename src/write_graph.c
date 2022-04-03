#include <stdio.h>
#include <stdlib.h>

typedef struct edges
{				  // lista krawędzi
	int start;	  // wierzchołek początkowy
	int end;	  // w. końcowy
	double value; // waga
	struct edges *next;
} * ptr;

ptr add_edge(ptr graph, int start, int end, double value)
{
	// dodaje krawędź na początek linked listy
	ptr nw = malloc(sizeof nw);

	nw->next = graph;
	nw->start = start;
	nw->end = end;
	nw->value = value;

	return nw;
}

int main(int argc, char **argv)
{
	int i, j;
	FILE *out = fopen(argv[1], "w");

	int c = 4; // liczba kolumn
	int r = 3; // liczba wierdszy

	ptr graph = NULL;

	for (i = 0; i < c * r - 1; i++)
	{
		if (i >= (c - 1) * r)
		{ // sprawdza czy wierzchołek jest w ostatnim wierszu
			graph = add_edge(graph, i, i + 1, 5);
			graph = add_edge(graph, i + 1, i, 5); // zamiana indeksów, żeby krawędź była w obie strony
		}
		else if (i % c == c - 1)
		{ // sprawdza czy wierzchołek jest  w ostatniej kolumnie
			graph = add_edge(graph, i, i + c, 5);
			graph = add_edge(graph, i + c, i, 5);
		}
		else
		{ // to się dzieje dla pozostałych wierzchołków
			graph = add_edge(graph, i, i + 1, 5);
			graph = add_edge(graph, i + 1, i, 5);
			graph = add_edge(graph, i, i + c, 5);
			graph = add_edge(graph, i + c, i, 5);
		}
	}

	// wypisywanie do pliku
	fprintf(out, "%d %d", r, c);
	for (i = 0; i < c * r; i++)
	{ // dla każdego wierzchołka
		fprintf(out, "\n");
		ptr tmp = graph;
		while (tmp != NULL)
		{ // przechodzi po liście krawędzi
			if (tmp->start == i)
			{ // i szuka krawędzi, których początkiem jest nasz wierzchołek
				fprintf(out, "%d :waga ", tmp->end);
			}
			tmp = tmp->next;
		}
	}

	return 0;
}

/*
// wersja z tablicą
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
*/
