#include <Adafruit_MCP3008.h>
#include <SPI.h>


// Define the number of MCP3008 chips connected
const int numChips = 2;


// Define the SPI CS (Chip Select) pins for each MCP3008 chip
const int csPins[] = {22, 24}; // Example: MCP3008 #1 CS pin = 10, MCP3008 #2 CS pin = 9


// Create an array of MCP3008 objects
Adafruit_MCP3008 mcp[numChips];


void setup() {
Serial.begin(115200);
SPI.begin(); // Initialize SPI communication


// Initialize each MCP3008 object with the corresponding CS pin
for (int i = 0; i < numChips; i++) {
  mcp[i].begin(csPins[i]);
  }
}


void loop() {
for (int i = 0; i < numChips; i++) {
// Read analog input from each MCP3008 channel (0-7)
  for (int channel = 0; channel < 8; channel++) {
    int value = mcp[i].readADC(channel);
      Serial.print("Chip ");
      Serial.print(i + 1);
      Serial.print(", Channel ");
      Serial.print(channel);
      Serial.print(": ");
      Serial.println(value);
    }
    Serial.println();
  }

  delay(250); // Wait for a second before reading again
}
