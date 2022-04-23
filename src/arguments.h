#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

void printHelp();
void checkArguments(int *setArguments, int genMode, int searchMode, int slpitMode);
void checkGenArgumentValues(int numOfColumns, int numOfRows, double minWeight, double maxWeight, int chance);
void checkSearchArgumentValues(int startVertex, int endVertex, int numOfRows, int numOfColumns);
void checkSplitArgumentValues(int startSplitVertex, int endSplitVertex, int numOfRows, int numOfColumns);

#endif