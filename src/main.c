#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

static void printHelp();
static void checkArguments(int optionIndex, int genMode, int searchMode);
static void checkArgumentValues(int numOfColumns, int numOfRows, double minWeight, double maxWeight, int chance);

int main(int argc, char **argv)
{
	int opt;

	int genMode = 0;
	int numOfColumns = 100;
	int numOfRows = 100;
	double minWeight = 1;
	double maxWeight = 100;
	int chance = 10;
	char *genGraphFileName = "graf_dane";

	int searchMode = 0;
	int startVertex;
	int endVertex;
	char *inFileName;
	char *outFileName;

	while (1)
	{
		int this_option_optind = optind ? optind : 1;
		int optionIndex = 0;

		static struct option longOptions[] = {
				{"gen", no_argument, 0, 0},					// 0
				{"nc", required_argument, 0, 0},		// 1
				{"nr", required_argument, 0, 0},		// 2
				{"minw", required_argument, 0, 0},	// 3
				{"maxw", required_argument, 0, 0},	// 4
				{"s", required_argument, 0, 0},			// 5
				{"file", required_argument, 0, 0},	// 6
				{"search", no_argument, 0, 0},			// 7
				{"start", required_argument, 0, 0}, // 8
				{"end", required_argument, 0, 0},		// 9
				{"in", required_argument, 0, 0},		// 10
				{"out", required_argument, 0, 0},		// 11
				{"h", required_argument, 0, 0},			// 12
				{0, 0, 0, 0}};

		opt = getOptLongOnly(argc, argv, "", longOptions, &optionIndex);

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
				chance = atoi(optarg);
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
				inFileName = inFileName;
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
		checkArguments(optionIndex, genMode, searchMode);
	}

	if (optind < argc)
	{
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		printf("\n");
	}

	checkArgumentValues(numOfColumns, numOfRows, minWeight, maxWeight, chance);
	// test - print all arguments values
	printf(
			" genMode = %d\n numOfColumns = %d\n numOfRows = %d\n minWeight = %g\n maxWeight = %g\n chance = %d\n genGraphFileName = %s\n searchMode = %d\n",
			genMode, numOfColumns, numOfRows, minWeight, maxWeight, chance, genGraphFileName, searchMode);

	if (genMode == 1)
	{
		// generate mode functionalities:
		// generate graph, write graph to file

		FILE *genGraphFile = fopen(genGraphFileName, "w");
		fprintf(genGraphFile,
						" genMode = %d\n numOfColumns = %d\n numOfRows = %d\n minWeight = %g\n maxWeight = %g\n chance = %d\n genGraphFileName = %s\n searchMode = %d\n",
						genMode, numOfColumns, numOfRows, minWeight, maxWeight, chance, genGraphFileName, searchMode);
	}

	if (searchMode == 1)
	{
		// search mode functionalities:
		// read graph from file to structure
		// BFS implementation - check if graph is connected
		// Dijkstra algorithm implementation - check the shortest path between two vertices
		// print out [is graph connected], [shortest path], [value of shortest path]
	}

	exit(EXIT_SUCCESS);
}

static void printHelp()
{
	char *usage =
			"Usage: The program can be called using two modes: \n"
			"-------------------------------------------------------------------------------\n"
			"-gen : Generator mode, program will generate the graph based on following flags: \n"
			"------------------------------------------------------------------------------- \n"
			"-nc cNum: \t cNum - Integer number of columns. Must be greater than 0 \n"
			"-nr rNum: \t rNum - Integer number of rows. Must be greater than 0 \n"
			"-minw minW: \t minW - Decimal number of minimal weight of the edge. Must be greater than 0\n"
			"-maxw maxW: \t maxW - Decimal number of maximal weight of the edge. Must be greater than k \n"
			"-s chance: \t chance - Integer number represanting % chance of NO existence of an edge between two vertices. Must be a value between 0 and 100\n"
			"-file file: \t file - Name of the file the graph will be generated to. \n\n"
			"-------------------------------------------------------------------------------\n"
			"-search : Search mode, program will find the shortest path between two given vertices: \n"
			"------------------------------------------------------------------------------- \n"
			"-start startV: \t startV - Integer number of starting vertex. Must fit in the number of graph's vertices.\n"
			"-end endV: \t endV - Integer number of ending vertex. Must fit in the number of graph's vertices.\n"
			"-in inFile: \t inFile - Name of the file the graph will be collected from\n"
			"-out outFile: \t outFile - Name of the file the graph will be inserted into\n\n"
			"-------------------------------------------------------------------------------\n"
			"-h - Prints out help menu.\n";

	fprintf(stdout, "%s", usage);
}

static void checkArguments(int optionIndex, int genMode, int searchMode)
{
	if ((optionIndex == 1 || optionIndex == 2 || optionIndex == 3 || optionIndex == 4 || optionIndex == 5 || optionIndex == 6) && (genMode == 0))
	{
		fprintf(stderr, "ERROR: You must firstly declare -gen mode before parsing gen argument.\n");
		exit(6);
	}
	if ((optionIndex == 8 || optionIndex == 9 || optionIndex == 10 || optionIndex == 11 && (searchMode == 0)))
	{
		fprintf(stderr, "ERROR: You must firstly declare -search mode before parsing search argument.\n");
		exit(6);
	}
}

static void checkArgumentValues(int numOfColumns, int numOfRows, double minWeight, double maxWeight, int chance)
{
	if (numOfColumns <= 0)
	{
		fprintf(stderr, "ERROR: Number of columns should represent a number greater than 0.\n");
		exit(8);
	}
	if (numOfRows <= 0)
	{
		fprintf(stderr, "ERROR: Number of rows should represent a number greater than 0.\n");
		exit(8);
	}
	if (minWeight <= 0)
	{
		fprintf(stderr, "ERROR: Weights values should be greater than 0.\n");
		exit(8);
	}
	if (maxWeight < minWeight)
	{
		fprintf(stderr, "ERROR: Maximal weight should be greater than minimal weight.\n");
		exit(8);
	}
	if (chance < 0 || chance > 100)
	{
		fprintf(stderr, "ERROR: Chance between no existing of an edge should be a value between 0 and 100");
	}
}
