#include <stdio.h>
#include <stdlib.h>

typedef struct kolejka
{
	int f;
	int r;
	int *arr;
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

int look_for_edge(int start, int end, double **graph, int c)
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

	// printf("jesteśmy w %d\n", current_v);
	visited[current_v] = 1;
	enqueue(queue, current_v);

	while (!isEmpty(queue))
	{
		current_v = dequeue(queue);
		// printf("jesteśmy w %d\n", current_v);
		for (i = 0; i < amount_of_v; i++)
		{
			if (visited[i] == 0 && look_for_edge(current_v, i, graph, c) == 1)
			{
				// printf("dodajemy do kol %d\n", i);
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

int dijkstra(double **graph, int c, int r, int start, int end)
{
	int i, j;
	int k = -1;
	int *visited = malloc(sizeof visited * (c * r));
	int *pred = malloc(sizeof pred * (c * r));
	double *dist = malloc(sizeof dist * (c * r));
	double min_dist;
	int count = 0;
	int next_node;
	for (i = 0; i < c * r; i++)
	{
		visited[i] = 0;
		pred[i] = start;
		dist[i] = 99999;
	}

	for (i = 0; i < 4; i++)
	{
		if (i == 0 && graph[start][i] != -1)
			k = start - 1;
		if (i == 1 && graph[start][i] != -1)
			k = start + 1;
		if (i == 2 && graph[start][i] != -1)
			k = start + c;
		if (i == 3 && graph[start][i] != -1)
			k = start - c;

		if (k != -1 && graph[start][i] != -1)
		{
			dist[k] = graph[start][i];
		}
	}
	visited[start] = 1;
	dist[start] = 0;
	count++;

	while (count < (c * r) - 1)
	{
		min_dist = 99999;
		for (i = 0; i < (c * r); i++)
		{
			if (dist[i] < min_dist && !visited[i])
			{
				min_dist = dist[i];
				next_node = i;
			}
		}
		visited[next_node] = 1;
		for (i = 0; i < 4; i++)
		{
			if (i == 0 && graph[next_node][i] != -1)
				k = next_node - 1;
			if (i == 1 && graph[next_node][i] != -1)
				k = next_node + 1;
			if (i == 2 && graph[next_node][i] != -1)
				k = next_node + c;
			if (i == 3 && graph[next_node][i] != -1)
				k = next_node - c;

			if (k != -1)
			{
				if (!visited[k] && min_dist + graph[next_node][i] < dist[k] && graph[next_node][i] != -1)
				{
					dist[k] = min_dist + graph[next_node][i];
					pred[k] = next_node;
				}
			}
		}
		count++;
	}
	for (i = 0; i < 12; i++)
	{
		printf("0 - %g\n", dist[i]);
	}
	for (i = 0; i < (c * r); i++)
	{
		if (i != start)
		{
			printf("\n dystans wezla %d = %g", i, dist[i]);
			printf("\nsciezka = %d", i);
			j = i;
			do
			{
				j = pred[j];
				printf("<-%d", j);
			} while (j != start);
		}
	}
}

int main(int argc, char **argv)
{
	int i, j;
	FILE *out = fopen(argv[1], "w");
	int c = 4;
	int r = 3;

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
	dijkstra(graph, c, r, 0, 7);
	return 0;
}