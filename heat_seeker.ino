#include <Adafruit_MLX90640.h>
#include "Adafruit_Arcada.h"
#include "src/functions.h"
#include "src/colour_pal.h"
#include <Servo.h>

// Objects
Servo myservo; 
Servo myservo2;
Adafruit_MLX90640 mlx;
Adafruit_Arcada arcada;

// Variables, Parameters
const int originalRows = 24;
const int originalCols = 32;
const int binSizeRow = 4;
const int binSizeCol = 4;
const int binnedRows = originalRows / binSizeRow;
const int binnedCols = originalCols / binSizeCol;
int hotspotRow;
int hotspotCol;
float servoRow = 135;
float servoCol = 90;
float row_correction;
float col_correction;
uint16_t white = 0xFFFF;
uint16_t red = 0xF800;
uint16_t displayPixelWidth, displayPixelHeight;

// Arrays
float frame[24*32]; // Sensor data
uint16_t colorPal[256]; // Color palette
float binnedData[6*8]; // Binned sensor data

// Set colour range. Too large, and the image will be hard to see.
#define MINTEMP 20
#define MAXTEMP 45


void setup() {

	// Switch on the Screen
	if (!arcada.arcadaBegin()) {
  		Serial.print("Failed to begin");
  		while (1);
  	}
	
	// Attach Servos
	myservo.attach(14);  
	myservo2.attach(15);
	myservo.write(servoCol);
	myservo2.write(servoRow);

	// Choose and Load Palette
	loadPalette(1, colorPal);

	// Setup Screen
	arcada.displayBegin();
	arcada.setBacklight(255);
	Serial.begin(115200);
	arcada.display->fillScreen(ARCADA_BLACK);
	displayPixelWidth = arcada.display->width() / 32;
	displayPixelHeight  = arcada.display->width() / 32; //Keep pixels square

	// Connect to Camera
	Serial.println("Adafruit MLX90640 Camera");
	if (! mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) {
		arcada.haltBox("MLX90640 not found!");
		}

	Serial.println("Found Adafruit MLX90640");
	Serial.print("Serial number: ");
	Serial.print(mlx.serialNumber[0], HEX);
	Serial.print(mlx.serialNumber[1], HEX);
	Serial.println(mlx.serialNumber[2], HEX);

	// Setup Camera
	mlx.setMode(MLX90640_CHESS);
	mlx.setResolution(MLX90640_ADC_19BIT);
	mlx.setRefreshRate(MLX90640_32_HZ);
	Wire.setClock(1000000); // max 1 MHz
}


void loop() {
 
	if (mlx.getFrame(frame) != 0) {
		Serial.println("Failed");
		return;
	}

	binData(binnedData, binnedRows, binnedCols, binSizeCol, binSizeRow, frame, originalRows, originalCols);
	findHotspotCoordinates(binnedData,hotspotRow, hotspotCol, binnedRows, binnedCols);
	
	// Map from the array representation to an angular representation
	// The binned 6x8 matrix is mapped to the FOV of the camera
    row_correction = map(hotspotRow,0, 5,17.5,-17.5);
    col_correction = map(hotspotCol,0, 7,-27.5, 27.5);

	// Derive the required row and column
    servoRow = servoRow + row_correction;
    servoRow = constrain(servoRow,90,180);
    servoCol = servoCol + col_correction;
    servoCol = constrain(servoCol,0,180);
	
	// Write to servos
	myservo.write(servoCol);
	delay(30);
	myservo2.write(servoRow);
	delay(30);  
  
	// Draw to screen
	for (uint8_t row=0; row<24; row++) {

		for (uint8_t col=0; col<32; col++) {

			float t = frame[row*32 + col];
			// Bound the temperature to desired range
			t = min(t, MAXTEMP);
			t = max(t, MINTEMP);
			// Map to a 8 bit number
			uint8_t colorIndex = map(t, MINTEMP, MAXTEMP, 0, 255);
			colorIndex = constrain(colorIndex, 0, 255);

			//draw the pixels!
			arcada.display->fillRect(displayPixelWidth * col, displayPixelHeight * row,
			displayPixelHeight, displayPixelWidth,
			colorPal[colorIndex]);
			}

	// Draw white bounding box around the 'hotspot'		
	arcada.display->drawRect(displayPixelWidth * hotspotCol * binSizeRow, displayPixelHeight * hotspotRow * binSizeRow,displayPixelHeight * binSizeRow, displayPixelWidth* binSizeRow, white);
	}
  

        
    

}
