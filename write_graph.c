#include <stdio.h>
#include <stdlib.h>

typedef struct kolejka	// oklejka do bfs
{
	int f;	// koniec kolejki
	int r;	// początek kolejki
	int *arr;	// kolejka
} * kol;

int isEmpty(kol queue)
{
	if (queue->f == queue->r)
		return 1;
	return 0;
}
void enqueue(kol queue, int ver)
{
	queue->arr[++queue->r] = ver;
}

int dequeue(kol queue)
{
	return queue->arr[++queue->f];
}

int look_for_edge(int start, int end, double **graph, int c)	// sprawdza czy istnieje polaczenie
{
	if ((end == start - 1 && graph[start][0] != -1) ||
		(end == start + 1 && graph[start][1] != -1) ||
		(end == start + c && graph[start][2] != -1) ||
		(end == start - c && graph[start][3] != -1))
		return 1;
	return 0;
}

int bfs(double **graph, int c, int r)
{
	int i;
	int amount_of_v = c * r;
	kol queue = malloc(sizeof queue);
	queue->arr = malloc(sizeof(int) * amount_of_v);
	queue->r = queue->f = -1;
	int current_v = 0;
	int *visited = malloc(sizeof(int) * amount_of_v);

	visited[current_v] = 1;
	enqueue(queue, current_v);

	while (!isEmpty(queue))
	{
		current_v = dequeue(queue);
		for (i = 0; i < amount_of_v; i++)
		{
			if (visited[i] == 0 && look_for_edge(current_v, i, graph, c) == 1)
			{
				visited[i] = 1;
				enqueue(queue, i);
			}
		}
	}
	for (i = 0; i < amount_of_v; i++)
		if (visited[i] == 0)
			return 0;
	return 1;
}

int main(int argc, char **argv)
{
	int i, j;
	FILE *out = fopen(argv[1], "w");
	int c = 200;
	int r = 200;

	double **graph = malloc(sizeof *graph * (r * c));
	for (i = 0; i < r * c; i++)
	{
		graph[i] = malloc(sizeof graph * 4);
		for (j = 0; j < 4; j++)
			graph[i][j] = -1;
	}

	for (i = 0; i < c * r - 1; i++)
	{
		if (i >= c * (r - 1))
		{ // sprawdza czy wierzchołek jest w ostatnim wierszu
			graph[i][1] = 10.3;
			graph[i + 1][0] = 10.3; // zamiana indeksów, żeby krawędź była w obie strony
		}
		else if (i % c == c - 1)
		{ // sprawdza czy wierzchołek jest  w ostatniej kolumnie
			graph[i][2] = 10.3;
			graph[i + c][3] = 10.3;
		}
		else
		{ // to się dzieje dla pozostałych wierzchołków
			graph[i][1] = 10.3;
			graph[i + 1][0] = 10.3;
			graph[i][2] = 10.3;
			graph[i + c][3] = 10.3;
		}
	}

	// wypisywanie do pliku
	fprintf(out, "%d %d\n", r, c);
	for (i = 0; i < c * r; i++)
	{ // dla każdego wierzchołka
		for (j = 0; j < 4; j++)
		{
			if (j == 0 && graph[i][j] != -1)
				fprintf(out, "%d :%g ", i - 1, graph[i][j]);
			if (j == 1 && graph[i][j] != -1)
				fprintf(out, "%d :%g ", i + 1, graph[i][j]);
			if (j == 2 && graph[i][j] != -1)
				fprintf(out, "%d :%g ", i + c, graph[i][j]);
			if (j == 3 && graph[i][j] != -1)
				fprintf(out, "%d :%g ", i - c, graph[i][j]);
		}
		fprintf(out, "\n");
	}

	printf("czy spojny: %d\n", bfs(graph, c, r));
	return 0;
}