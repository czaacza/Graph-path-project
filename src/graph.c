#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

// typedef struct
// {
// 	double **values;
// 	int numOfColumns;
// 	int numOfRows;
// } * graph_t;

graph_t createGraph()
{
    graph_t newGraph = malloc(sizeof *newGraph);
    if (newGraph == NULL)
    {
        fprintf(stderr, "ERROR: Memory for graph unsuccesfully allocated.\n");
        exit(1);
    }

    return newGraph;
}

static void initGraphValues(graph_t graph, int numOfRows, int numOfColumns)
{

    graph->values = malloc(sizeof(double *) * numOfRows * numOfColumns);

    for (int i = 0; i < numOfRows * numOfColumns; i++)
    {
        graph->values[i] = malloc(4 * sizeof(double));
    }

    if (graph->values == NULL)
    {
        fprintf(stderr, "ERROR: Memory for vertices unsuccesfully allocated.\n");
        exit(1);
    }
}

int loadGraph(graph_t graph, char *fileName)
{
    FILE *inFile = fopen(fileName, "r");

    if (inFile == NULL)
    {
        return 3;
    }

    if (fscanf(inFile, "%d %d", &(graph->numOfRows), &(graph->numOfColumns)) != 2)
    {
        fprintf(stderr, "Reading numOfRows and numOfColumns from file %s failed.\n", fileName);
        return 3;
    }

    initGraphValues(graph, graph->numOfRows, graph->numOfColumns);

    int lineNum = 1;
    int vertexNum = lineNum - 2;
    int a;
    int c;

    while ((c = fgetc(inFile)) != EOF)
    {
        if (c == '\n')
        {
            printf("\n");
            lineNum++;
            vertexNum++;
        }

        if (isspace(c))
        {
            continue;
        }
        if (isdigit(c))
        {
            ungetc(c, inFile);
            int checkedVertex; // pobrany numer wierzcholka do ktorego mamy wage
            double weightValue;
            fscanf(inFile, "%d :%lf", &(checkedVertex), &(weightValue));

            printf(" vertexNum = %d checkedVertex = %d weightValue = %g ", vertexNum, checkedVertex, weightValue);

            if (checkedVertex == (vertexNum - graph->numOfColumns))
            {
                graph->values[vertexNum][0] = weightValue;
            }
            else if (checkedVertex == (vertexNum + 1))
            {
                graph->values[vertexNum][1] = weightValue;
            }
            else if (checkedVertex == (vertexNum + graph->numOfColumns))
            {
                graph->values[vertexNum][2] = weightValue;
            }
            else if (checkedVertex == (vertexNum - 1))
            {
                graph->values[vertexNum][3] = weightValue;
            }
            else
            {
                fprintf(stderr, "ERROR: Graph uncessfully loaded. %s has wrong file format.", fileName);
            }

            continue;
        }
    }
    printf(" Line num: %d\n", lineNum);
    printf(" NumOfRows = %d\n NumOfColumns = %d\n", graph->numOfRows, graph->numOfColumns);
}

graph_t generateGraph()
{
}

int saveGraph()
{
}

void printGraph(graph_t graph)
{
    for (int i = 0; i < graph->numOfRows * graph->numOfColumns; i++)
    {
        printf("W.%d ", i);
        printf("values = [ ");
        for (int j = 0; j < 4; j++)
        {
            printf("%g ", graph->values[i][j]);
        }
        printf("]\n");
    }
}