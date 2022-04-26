#include <stdio.h>
#include <stdlib.h>
#include "arguments.h"

void printHelp()
{
	char *usage =
		"Usage: The program can be called using three modes: \n"
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
		"-out outFile: \t outFile - Name of the file the shortest path and length will be inserted to.\n\n"
		"-------------------------------------------------------------------------------\n"
		"-split : Split mode, program will split graph (given after the option -in) along the shortest path between two given vertices\n"
		"-------------------------------------------------------------------------------\n"
		"-splits startS: \t startS - Integer number of starting vertex. Starting vertex must be in the first row of the graph\n"
		"-splite endS: \t endS - Integer number of ending vertex. Ending vertex must be in the last row of the graph\n"
		"-splitout outSplitFile: \t outSplitFile - Name of the file the splited graph will be generated to\n\n"
		"-------------------------------------------------------------------------------\n"
		"-h - Prints out help menu.\n\n";

	fprintf(stdout, "%s", usage);
}

void checkArguments(int *setArguments, int genMode, int searchMode, int splitMode)
{
	int arg;

	for (arg = 1; arg <= 6; arg++)
	{
		if (setArguments[arg] == 1 && genMode == 0)
		{
			fprintf(stderr, "ERROR: You must firstly declare -gen mode before parsing gen argument.\n");
			exit(6);
		}
	}
	for (arg = 8; arg <= 11; arg++)
	{
		if (arg == 10)
		{ // -in file is the same for both modes
			if (setArguments[arg] == 1 && searchMode == 0 && splitMode == 0)
			{
				fprintf(stderr, "ERROR: You must firstly declare -search or -split mode before parsing search/split argument.\n");
				exit(6);
			}
			continue;
		}
		if (setArguments[arg] == 1 && searchMode == 0)
		{
			fprintf(stderr, "ERROR: You must firstly declare -search mode before parsing search argument.\n");
			exit(6);
		}
	}
	for (arg = 13; arg <= 15; arg++)
	{
		if (setArguments[arg] == 1 && splitMode == 0)
		{
			fprintf(stderr, "ERROR: You must firstly declare -split mode before parsing split argument.\n");
			exit(6);
		}
	}
	if ((setArguments[8] == 0) && searchMode == 1)
	{
		fprintf(stderr, "ERROR: Starting vertex not defined.");
		exit(6);
	}
	if ((setArguments[9] == 0) && searchMode == 1)
	{
		fprintf(stderr, "ERROR: Ending vertex not defined.");
		exit(6);
	}
	if ((setArguments[13] == 0) && splitMode == 1)
	{
		fprintf(stderr, "ERROR: Starting split vertex not defined.");
		exit(6);
	}
	if ((setArguments[14] == 0) && splitMode == 1)
	{
		fprintf(stderr, "ERROR: Ending split vertex not defined.");
		exit(6);
	}
}

void checkGenArgumentValues(int numOfColumns, int numOfRows, double minWeight, double maxWeight, int chance)
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
	if (minWeight <= 0 || minWeight >= 1000)
	{
		fprintf(stderr, "ERROR: Weights values should be greater than 0 and less than 1000.\n");
		exit(8);
	}
	if (maxWeight < minWeight || maxWeight >= 1000)
	{
		fprintf(stderr, "ERROR: Maximal weight should be greater than minimal weight and less than 1000.\n");
		exit(8);
	}
	if (chance < 0 || chance > 100)
	{
		fprintf(stderr, "ERROR: Chance of no existing of an edge should be a value between 0 and 100\n");
		exit(8);
	}
}

void checkSearchArgumentValues(int startVertex, int endVertex, int numOfRows, int numOfColumns)
{
	if (startVertex < 0 || startVertex >= numOfColumns * numOfRows)
	{
		fprintf(stderr, "ERROR: Starting vertex should be greater than or equal to 0 and less than number of vertices.\n");
		exit(8);
	}
	if (endVertex < 0 || endVertex >= numOfColumns * numOfRows)
	{
		fprintf(stderr, "ERROR: Ending vertex should be greater than or equal to 0 and less than number of vertices.\n");
		exit(8);
	}
}

void checkSplitArgumentValues(int startSplitVertex, int endSplitVertex, int numOfRows, int numOfColumns)
{
	if (startSplitVertex == endSplitVertex)
	{
		fprintf(stderr, "ERROR: Split starting and ending vertices are the same. You cannot split a graph this way\n");
		exit(8);
	}

	if (startSplitVertex < 0 || startSplitVertex >= numOfColumns * numOfRows || !isVertexEdge(startSplitVertex, numOfRows, numOfColumns))
	{
		fprintf(stderr, "ERROR: Split starting vertex should be on the edge of graph.\n\nGraph edges reach following value ranges: \n");
		fprintf(stderr, "Top edge:\t<0 ; %d> \n", numOfColumns - 1);
		fprintf(stderr, "Bottom edge:\t<%d ; %d> \n", (numOfRows * numOfColumns) - numOfColumns, (numOfRows * numOfColumns) - 1);
		fprintf(stderr, "Right edge:\t%d + multiple of %d <%d ; %d> \n", numOfColumns - 1, numOfColumns, numOfColumns - 1, (numOfRows * numOfColumns) - 1);
		fprintf(stderr, "Left edge:\tmultiple of %d <0 ; %d> \n\n", numOfColumns, (numOfRows * numOfColumns) - numOfColumns);
		exit(8);
	}

	if (endSplitVertex < 0 || endSplitVertex >= numOfColumns * numOfRows || !isVertexEdge(endSplitVertex, numOfRows, numOfColumns))
	{
		fprintf(stderr, "ERROR: Split ending vertex should be on the edge of graph.\n\nGraph edges reach following value ranges: \n");
		fprintf(stderr, "Top edge:\t<0 ; %d> \n", numOfColumns - 1);
		fprintf(stderr, "Bottom edge:\t<%d ; %d> \n", (numOfRows * numOfColumns) - numOfColumns, (numOfRows * numOfColumns) - 1);
		fprintf(stderr, "Right edge:\t%d + multiple of %d <%d ; %d> \n", numOfColumns - 1, numOfColumns, numOfColumns - 1, (numOfRows * numOfColumns) - 1);
		fprintf(stderr, "Left edge:\tmultiple of %d <0 ; %d> \n\n", numOfColumns, (numOfRows * numOfColumns) - numOfColumns);
		exit(8);
	}
}

int isVertexEdge(int vertex, int numOfRows, int numOfColumns)
{
	if (vertex >= 0 && vertex <= numOfColumns - 1)
	{
		return 1;
	}
	else if (vertex >= (numOfRows * numOfColumns) - numOfColumns && vertex <= (numOfRows * numOfColumns) - 1)
	{
		return 1;
	}
	else if (vertex >= numOfColumns - 1 && vertex <= (numOfRows * numOfColumns) - 1 && (vertex - (numOfColumns - 1)) % numOfColumns == 0)
	{
		return 1;
	}
	else if (vertex >= 0 && vertex <= (numOfRows * numOfColumns) - numOfColumns && vertex % numOfColumns == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
