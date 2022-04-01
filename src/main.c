#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

static void printHelp()
{
  char *usage =
      "Usage: The program can be called using two modes: \n"
      "-------------------------------------------------------------------------------\n"
      "-g : Generator mode, program will generate the graph based on following flags: \n"
      "------------------------------------------------------------------------------- \n"
      "-c cNum: \t cNum - Integer number of columns. Must be greater than 0 \n"
      "-r rNum: \t rNum - Integer number of rows. Must be greater than 0 \n"
      "-m minW: \t minW - Decimal number of minimal weight of the edge. Must be greater than 0\n"
      "-x maxW: \t maxW - Decimal number of maximal weight of the edge. Must be greater than k \n"
      "-z chance: \t chance - Integer number represanting % chance of NO existence of an edge between two vertices. Must be a value between 0 and 100\n"
      "-f file: \t file - Name of the file the graph will be generated to. \n\n"
      "-------------------------------------------------------------------------------\n"
      "-p : Path mode, program will find the shortest path between two given vertices: \n"
      "------------------------------------------------------------------------------- \n"
      "-s startV: \t startV - Integer number of starting vertex. Must fit in the number of graph's vertices.\n"
      "-e endV: \t endV - Integer number of ending vertex. Must fit in the number of graph's vertices.\n"
      "-i inFile: \t inFile - Name of the file the graph will be collected from\n"
      "-o outFile: \t outFile - Name of the file the graph will be inserted into\n\n"
      "-------------------------------------------------------------------------------\n"
      "-h - Prints out help menu.\n";

  fprintf(stdout, "%s", usage);
}

// static int checkArguments(g, c, r, m, x, z, f, p, s, e, i, o)
// {
//   if (g == 1)
//   {
//     if (c < 0)
//     {
//       return
//     }
//   }
// }

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

  int pathMode = 0;
  int startVertex;
  int endVertex;
  char *inFileName;
  char *outFileName;

  while ((opt = getopt(argc, argv, "g:c:r:m:x:z:f:p:s:e:i:o:h")) != -1)
  {
    switch (opt)
    {
    case 'g':
      genMode = 1;
      break;
    case 'c':
      if (genMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on gen mode.");
        return 6;
      }
      numOfColums = atoi(optarg);

      break;
    case 'r':
      if (genMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on gen mode.");
        return 6;
      }
      numOfRows = atoi(optarg);
      break;
    case 'm':
      if (genMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on gen mode.");
        return 6;
      }
      minWeight = atof(optarg);
      break;
    case 'x':
      if (genMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on gen mode.");
        return 6;
      }
      maxWeight = atof(optarg);
      break;
    case 'z':
      if (genMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on gen mode.");
        return 6;
      }
      chance = atoi(optarg);
      break;
    case 'f':
      if (genMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on gen mode.");
        return 6;
      }
      genGraphFileName = optarg;
      break;
    case 'p':
      pathMode = 1;
      break;
    case 's':
      if (pathMode == 0)
      {
        fprintf(stderr, "%s: %s\n", argv[0], "You selected path mode argument without turning on the path mode.");
        return 6;
      }
      startVertex = atoi(optarg);
      break;
    case 'e':
      if (pathMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on the path mode.");
        return 6;
      }
      endVertex = atoi(optarg);
      break;
    case 'i':
      if (pathMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on the path mode.");
        return 6;
      }
      inFileName = inFileName;
      break;
    case 'o':
      if (pathMode == 0)
      {
        fprintf(stderr, "%s\n", "You selected path mode argument without turning on the path mode.");
        return 6;
      }
      outFileName = optarg;
      break;
    case 'h':
      printHelp();
      break;

    default:
      // print help
      return 6;
    }
  }

  return EXIT_SUCCESS;
}
