#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"

void loadGraph(graph_t graph, char *inFileName)
{
  FILE *inFile = fopen(inFileName, "r");

  if (inFile == NULL)
  {
    fprintf(stderr, "ERROR: Couldn't find input file named '%s'\n", inFileName);
    exit(3);
  }

  if (fscanf(inFile, "%d %d", &(graph->numOfRows), &(graph->numOfColumns)) != 2)
  {
    fprintf(stderr, "Reading numOfRows and numOfColumns from file %s failed.\n", inFileName);
    exit(3);
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
  fclose(inFile);
}

void saveGraph(graph_t graph, char *outFileName)
{
  FILE *outFile = fopen(outFileName, "w");
  if (outFile == NULL)
  {
    fprintf(stderr, "ERROR: Couldn't open file named '%s'\n", outFileName);
    exit(4);
  }

  fprintf(outFile, "%d %d\n", graph->numOfRows, graph->numOfColumns);
  for (int vertice = 0; vertice < graph->numOfColumns * graph->numOfRows; vertice++)
  {
    for (int i = 0; i < 4; i++)
    {
      if (graph->values[vertice][i])
      {
        switch (i)
        {
        case 0:
          fprintf(outFile, "%d :%g ", vertice - graph->numOfColumns, graph->values[vertice][i]);
          break;
        case 1:
          fprintf(outFile, "%d :%g ", vertice + graph->numOfColumns, graph->values[vertice][i]);
          break;
        case 2:
          fprintf(outFile, "%d :%g ", vertice + 1, graph->values[vertice][i]);
          break;
        case 3:
          fprintf(outFile, "%d :%g ", vertice - 1, graph->values[vertice][i]);
          break;
        }
      }
    }
    fprintf(outFile, "\n");
  }
  fclose(outFile);
}