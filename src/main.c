#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

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
		"-search : Path mode, program will find the shortest path between two given vertices: \n"
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
		printf("%s", "You must firstly declare -gen mode before parsing gen argument.\n");
		exit(6);
	}
	if ((optionIndex == 8 || optionIndex == 9 || optionIndex == 10 || optionIndex == 11 && (searchMode == 0)))
	{
		printf("%s", "You must firstly declare -search mode before parsing search argument.\n");
		exit(6);
	}
}

static void checkArgumentValues(int numOfColumns, int numOfRows, double minWeight, double maxWeight, int chance)
{
	if (numOfColumns <= 0)
	{
		printf("Number of columns should be greater than 0.\n");
		exit(8);
	}
	if (numOfRows <= 0)
	{
		printf("Number of rows should be greater than 0.\n");
		exit(8);
	}
	if (minWeight <= 0)
	{
		printf("Weights values should be greater than 0.\n");
		exit(8);
	}
	if (maxWeight < minWeight)
	{
		printf("Maximal weight should be greater than minimal weight.\n");
		exit(8)
	}
	if (chance < 0 || chance > 100)
	{
		printf("Chance between no existing of an edge should be a value between 0 and 100");
	}
}

int main(int argc, char **argv)
{

	int numOfArguments = argc;
	int opt;

	int genMode = 0;
	int numOfColums = 100;
	int numOfRows = 100;
	double minWeight = 1;
	double maxWeight = 100;
	int chance = 10;
	char *genGraphFileName;

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
			{"h", required_argument, 0, 0},		// 12
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
				numOfColums = atoi(optarg);
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

	exit(EXIT_SUCCESS);
}