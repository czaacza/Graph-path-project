#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{

    graph_t graph = createGraph();
    loadGraph(graph, "dane");

    printGraph(graph);

    return 0;
}