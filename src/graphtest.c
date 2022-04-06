#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{

    graph_t graph = createGraph();
    loadGraph(graph, "dane");
    // for (int i = 0; i < graph->numOfRows * graph->numOfColumns; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         graph->values[i][j] = i * j;
    //     }
    // }

    for (int i = 0; i < graph->numOfRows * graph->numOfColumns; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%g\t", graph->values[i][j]);
        }
        printf("\n");
    }

    return 0;
}