#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

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

int loadGraph(graph_t graph, char *inFileName)
{
    FILE *inFile = fopen(inFileName, "r");

    if (inFile == NULL)
    {
        fprintf(stderr, "ERROR: Couldn't find input file named '%s'\n", inFileName);
        return 3;
    }

    if (fscanf(inFile, "%d %d", &(graph->numOfRows), &(graph->numOfColumns)) != 2)
    {
        fprintf(stderr, "Reading numOfRows and numOfColumns from file %s failed.\n", inFileName);
        return 3;
    }

    initGraphValues(graph, graph->numOfRows, graph->numOfColumns);

    int vertexNum = -1;
    int c;

    while ((c = fgetc(inFile)) != EOF)
    {
        if (c == '\n')
        {
            vertexNum++;
        }

        if (isspace(c))
        {
            continue;
        }
        if (isdigit(c))
        {
            ungetc(c, inFile);
            int checkedVertex;
            double weightValue;
            fscanf(inFile, "%d :%lf", &(checkedVertex), &(weightValue));

            if (checkedVertex == (vertexNum - graph->numOfColumns))
            {
                graph->values[vertexNum][0] = weightValue;
            }

            else if (checkedVertex == (vertexNum + graph->numOfColumns))
            {
                graph->values[vertexNum][1] = weightValue;
            }

            else if (checkedVertex == (vertexNum + 1))
            {
                graph->values[vertexNum][2] = weightValue;
            }

            else if (checkedVertex == (vertexNum - 1))
            {
                graph->values[vertexNum][3] = weightValue;
            }
            else
            {
                fprintf(stderr, "ERROR: Couldn't load the graph. %s has wrong file format.\n", inFileName);
                exit(3);
            }

            continue;
        }
    }
}

int saveGraph(graph_t graph, char *outFileName)
{
    FILE *outFile = fopen(outFileName, "w");
    if (outFile == NULL)
    {
        fprintf(stderr, "ERROR: Couldn't open file named '%s'\n", outFileName);
        return 4;
    }

    fprintf(outFile, "%d %d\n", graph->numOfRows, graph->numOfColumns);
    for (int vertice = 0; vertice < graph->numOfColumns * graph->numOfRows; vertice++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (graph->values[vertice][i])
            {
                if (i == 0)
                    fprintf(outFile, "%d :%g ", vertice - graph->numOfColumns, graph->values[vertice][i]);
                if (i == 1)
                    fprintf(outFile, "%d :%g ", vertice + graph->numOfColumns, graph->values[vertice][i]);
                if (i == 2)
                    fprintf(outFile, "%d :%g ", vertice + 1, graph->values[vertice][i]);
                if (i == 3)
                    fprintf(outFile, "%d :%g ", vertice - 1, graph->values[vertice][i]);
            }
        }
        fprintf(outFile, "\n");
    }
}

graph_t generateGraph()
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