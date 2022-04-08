#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{

    graph_t graph = createGraph();
    loadGraph(graph, "data/dane");
    printGraph(graph);
    saveGraph(graph, "data/graf_dane");

    return 0;
}