#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <Arduino.h>


void binData(float binnedData[], int binnedRows, int binnedCols, int binSizeCol, int binSizeRow, float frame[], int originalRows, int originalCols);

void findHotspotCoordinates(float frame[], int &set_row, int &set_col, int originalRows, int originalCols);

void printFlattenedAs2D(float arr[], int rows, int cols);

#endif 
