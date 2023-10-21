#include <Wire.h>
#include <INA226_WE.h>  // Include the INA226 library & ensure it's in the Arduino libraries folder

// Define the I2C addresses of your INA226 modules
const int numDevices = 5;
const uint8_t addresses[numDevices] = {0x40, 0x41, 0x42, 0x43, 0x44}; // Replace with your INA226 addresses

INA226_WE ina226[numDevices];

void setup() {
    Serial.begin(115200);  // Start serial communication at a baud rate of 115200
    Wire.begin();  // Initiate the Wire library

    // Initialize each INA226 module
    for (int i = 0; i < numDevices; ++i) {
        ina226[i].init(addresses[i]);
        // Additional setup for the INA226 can be performed here
        // For example, setting the calibration value or configuring alert parameters
    }
}

void loop() {
    for (int i = 0; i < numDevices; ++i) {
        float shuntVoltage_mV = ina226[i].getShuntVoltage_mV();
        float busVoltage_V = ina226[i].getBusVoltage_V();
        float current_mA = ina226[i].getCurrent_mA();
        float power_mW = ina226[i].getPower_mW();

        // Output the readings to the Serial Monitor
        Serial.print("Device ");
        Serial.print(i);
        Serial.print(": Voltage: ");
        Serial.print(busVoltage_V);
        Serial.print("V, Current: ");
        Serial.print(current_mA);
        Serial.print("mA, Power: ");
        Serial.print(power_mW);
        Serial.println("mW");
    }

    delay(1000);  // Delay before the next set of readings
}