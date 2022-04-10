#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "graph.h"
#include "generate.h"
#include "bfs.h"
#include "search.h"
#include "arguments.h"

int main(int argc, char **argv)
{
	int opt;

	int genMode = 0;
	int numOfColumns = 100;
	int numOfRows = 100;
	double minWeight = 1;
	double maxWeight = 100;
	double chance = 10;
	char *genGraphFileName = "data/graf_dane";
	int searchMode = 0;
	int startVertex;
	int endVertex;
	char *inFileName = "data/graf_dane";
	char *outFileName;

	int *setArguments = calloc(14, sizeof(int));

	while (1)
	{
		int this_option_optind = optind ? optind : 1;
		int optionIndex = 0;

		static struct option longOptions[] = {
			{"gen", no_argument, 0, 0},			// 0
			{"nc", required_argument, 0, 0},	// 1
			{"nr", required_argument, 0, 0},	// 2
			{"minw", required_argument, 0, 0},	// 3
			{"maxw", required_argument, 0, 0},	// 4
			{"s", required_argument, 0, 0},		// 5
			{"file", required_argument, 0, 0},	// 6
			{"search", no_argument, 0, 0},		// 7
			{"start", required_argument, 0, 0}, // 8
			{"end", required_argument, 0, 0},	// 9
			{"in", required_argument, 0, 0},	// 10
			{"out", required_argument, 0, 0},	// 11
			{"h", no_argument, 0, 0},			// 12
			{0, 0, 0, 0}};

		opt = getopt_long_only(argc, argv, "", longOptions, &optionIndex);

		if (opt == -1)
		{
			break;
		}
		switch (opt)
		{
		case 0:
			switch (optionIndex)
			{
			case 0:
				genMode = 1;
				break;
			case 1:
				numOfColumns = atoi(optarg);
				break;
			case 2:
				numOfRows = atoi(optarg);
				break;
			case 3:
				minWeight = atof(optarg);
				break;
			case 4:
				maxWeight = atof(optarg);
				break;
			case 5:
				chance = atof(optarg);
				break;
			case 6:
				genGraphFileName = optarg;
				break;
			case 7:
				searchMode = 1;
				break;
			case 8:
				startVertex = atoi(optarg);
				break;
			case 9:
				endVertex = atoi(optarg);
				break;
			case 10:
				inFileName = optarg;
				break;
			case 11:
				outFileName = optarg;
				break;
			case 12:
				printHelp();
				break;
			}
			break;

		case '?':
			printf("Incorrect option, try ./a.out -h\n");
			break;

		default:
			printHelp();
		}
		setArguments[optionIndex] = 1;
	}

	if (optind < argc)
	{
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}
	checkArguments(setArguments, genMode, searchMode);

	// printf(
	// 		" genMode = %d\n numOfColumns = %d\n numOfRows = %d\n minWeight = %g\n maxWeight = %g\n chance = %g\n genGraphFileName = %s\n searchMode = %d\n startVertex = %d\n endVertex = %d\n inFileName = %s\n outFileName = %s\n",
	// 		genMode, numOfColumns, numOfRows, minWeight, maxWeight, chance, genGraphFileName, searchMode, startVertex, endVertex, inFileName, outFileName);

	// printf("set arguments: ");
	// for (int i = 0; i < 14; i++)
	// {
	// 	printf("%d ", setArguments[i]);
	// }
	// printf("\n");

	graph_t graph = createGraph();
	graph->numOfColumns = numOfColumns;
	graph->numOfRows = numOfRows;

	if (genMode == 1)
	{
		// generate mode functionalities:
		// generate graph, write graph to file
		checkGenArgumentValues(numOfColumns, numOfRows, minWeight, maxWeight, chance);

		initGraphValues(graph, numOfRows, numOfColumns);
		genGraph(graph, chance, minWeight, maxWeight);
		saveGraph(graph, genGraphFileName);
	}

	if (searchMode == 1)
	{
		loadGraph(graph, inFileName);
		numOfRows = graph->numOfRows;
		numOfColumns = graph->numOfColumns;
		checkSearchArgumentValues(startVertex, endVertex, numOfRows, numOfColumns);

		FILE *outFile;
		if (setArguments[11] == 1)
		{
			outFile = fopen(outFileName, "w");
			if (outFile == NULL)
			{
				fprintf(stderr, "ERROR: Couldn't open file named '%s'\n", outFileName);
				exit(4);
			}
		}
		else
		{
			outFile = stdout;
		}

		if (bfs(graph) == 1)
		{
			fprintf(outFile, "Graph is connected\n");
		}
		else
		{
			fprintf(outFile, "Graf is not connected\n");
		}

		returnValues_t returnedValues = dijkstra(graph, startVertex, endVertex);
		printReturnedValues(outFile, outFileName, returnedValues, startVertex, endVertex);
	}

	freeGraph(graph);
	exit(EXIT_SUCCESS);
}
