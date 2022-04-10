#include <stdio.h>
#include <stdlib.h>

void printHelp()
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
      "-out outFile: \t outFile - Name of the file the shortest path and length will be inserted to.\n\n"
      "-------------------------------------------------------------------------------\n"
      "-h - Prints out help menu.\n";

  fprintf(stdout, "%s", usage);
}

void checkArguments(int *setArguments, int genMode, int searchMode)
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
    if (setArguments[arg] == 1 && searchMode == 0)
    {
      fprintf(stderr, "ERROR: You must firstly declare -search mode before parsing search argument.\n");
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
    fprintf(stderr, "ERROR: Chance of no existing of an edge should be a value between 0 and 100\n");
    exit(8);
  }
}

void checkSearchArgumentValues(int startVertex, int endVertex, int numOfRows, int numOfColumns)
{
  if (startVertex < 0 || startVertex >= numOfColumns * numOfRows)
  {
    fprintf(stderr, "ERROR: Starting vertex should be greater and equal than 0 and less than number of vertices.\n");
    exit(8);
  }
  if (endVertex < 0 || endVertex >= numOfColumns * numOfRows)
  {
    fprintf(stderr, "ERROR: Ending vertex should be greater and equal than 0 and less than number of vertices.\n");
    exit(8);
  }
}