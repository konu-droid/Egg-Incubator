
// /********************************************************************/

// // First we include the libraries
// #include <OneWire.h> 
// #include <DallasTemperature.h>
// /********************************************************************/
// // Data wire is plugged into pin 2 on the Arduino 
// #define ONE_WIRE_BUS 2 
// /********************************************************************/
// // Setup a oneWire instance to communicate with any OneWire devices  
// // (not just Maxim/Dallas temperature ICs) 
// OneWire oneWire(ONE_WIRE_BUS); 
// /********************************************************************/
// // Pass our oneWire reference to Dallas Temperature. 
// DallasTemperature sensors(&oneWire);
// /********************************************************************/ 
// void setup(void) 
// { 
//  // start serial port 
//  Serial.begin(9600); 
//  Serial.println("Dallas Temperature IC Control Library Demo"); 
//  // Start up the library 
//  sensors.begin(); 
// } 
// void loop(void) 
// { 
//  // call sensors.requestTemperatures() to issue a global temperature 
//  // request to all devices on the bus 
// /********************************************************************/
//  Serial.print(" Requesting temperatures..."); 
//  sensors.requestTemperatures(); // Send the command to get temperature readings 
//  Serial.println("DONE"); 
// /********************************************************************/
//  Serial.print("Temperature is: "); 
//  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
//    // You can have more than one DS18B20 on the same bus.  
//    // 0 refers to the first IC on the wire 
//    delay(1000); 
// } 


// Example testing sketch for various DHT humidity/temperature sensors

#include "DHT.h"
#define DHTPIN 2 // what digital pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors. This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
   Serial.begin(9600);
   Serial.println("DHTxx test!");
   dht.begin();
}

void loop() {
   delay(2000); // Wait a few seconds between measurements
   float h = dht.readHumidity();
   // Reading temperature or humidity takes about 250 milliseconds!
   float t = dht.readTemperature();
   // Read temperature as Celsius (the default)
   float f = dht.readTemperature(true);
   // Read temperature as Fahrenheit (isFahrenheit = true)
   // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   
   // Compute heat index in Fahrenheit (the default)
   float hif = dht.computeHeatIndex(f, h);
   // Compute heat index in Celsius (isFahreheit = false)
   float hic = dht.computeHeatIndex(t, h, false);
   Serial.print ("Humidity: ");
   Serial.print (h);
   Serial.print (" %\t");
   Serial.print ("Temperature: ");
   Serial.print (t);
   Serial.print (" *C ");
   Serial.print (f);
   Serial.print (" *F\t");
   Serial.print ("Heat index: ");
   Serial.print (hic);
   Serial.print (" *C ");
   Serial.print (hif);
   Serial.println (" *F");
}
