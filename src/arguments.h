#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H

void printHelp();
void checkArguments(int *setArguments, int genMode, int searchMode);
void checkGenArgumentValues(int numOfColumns, int numOfRows, double minWeight, double maxWeight, int chance);
void checkSearchArgumentValues(int startVertex, int endVertex, int numOfRows, int numOfColumns);

#endif