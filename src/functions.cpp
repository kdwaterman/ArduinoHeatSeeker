#include "functions.h"


/* Bin Data
Take averages of groups of pixels and populate reduced array. Reduces noise in the sensor for better detection and tracking.
*/
void binData(float binnedData[], int binnedRows, int binnedCols, int binSizeCol, int binSizeRow, float frame[], int originalRows, int originalCols) {

	for (int row = 0; row < binnedRows; row++) {
		for (int col = 0; col < binnedCols; col++) {
			
			float sum = 0.0;
			
			for (int x = 0; x < binSizeRow; x++) {

				for (int y = 0; y < binSizeCol; y++) {

			    	sum += frame[(row * binSizeRow + x) * originalCols + (col * binSizeCol + y)];
					
					}
				}

				binnedData[row * binnedCols + col] = sum / (binSizeRow * binSizeCol);
			}
		}
	}



/* Find Hotspot
Find maximum within array.
*/
void findHotspotCoordinates(float frame[], int &set_row, int &set_col, int originalRows, int originalCols) {

	float maxTemp = 0;

	for (int row = 0; row < originalRows; row++) {
		for (int col = 0; col < originalCols; col++) {
			if (frame[ originalCols * row + col] > maxTemp) {

				maxTemp = frame[ originalCols * row + col] ;
				set_row = row;
				set_col = col;
				}
			}
		}
}

/* Print array
Prints a flattened array as if it was 2D.
*/

void printFlattenedAs2D(float arr[], int rows, int cols) {

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {

			int index = row * cols + col;  // Calculate the index in the 1D array
			Serial.print(arr[index]);

			if (col < cols - 1) {

				Serial.print(", ");  // Delimiter for columns
				
				}
			}
		Serial.println();  // Newline for each row
		}
}




