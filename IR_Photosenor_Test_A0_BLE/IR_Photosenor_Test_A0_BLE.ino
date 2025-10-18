/*
 * Simple IR Sensor Test Code
 * Arduino Nano 33 BLE Sense Rev2
 * 
 * Tests BPW34 + LM358 IR detector circuit
 * LED brightness increases with IR signal strength
 */

// ========== PIN DEFINITIONS ==========
const int IR_SENSOR_PIN = A0;  // IR sensor output from LM358

// RGB LED pins (Nano 33 BLE Sense built-in)
// int LED_RED = 22;
// const int LED_GREEN = 23;
// const int LED_BLUE = 24;

// ========== SETUP ==========
void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000);  // Wait up to 3 seconds for serial
  
  Serial.println("============================");
  Serial.println("IR Sensor Test - SIMPLE");
  Serial.println("============================");
  Serial.println("Point IR LED at BPW34 sensor");
  Serial.println("LED will brighten with IR intensity\n");
  
  // Initialize pins
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Turn LED off initially
  setLED(0, 0, 0);
  
  delay(1000);
  Serial.println("Ready! Watching for IR...\n");
}

// ========== MAIN LOOP ==========
void loop() {
  // Read IR sensor (0-1023 from ADC)
  int sensorValue = analogRead(IR_SENSOR_PIN);
  
  // Map sensor reading to LED brightness (0-255)
  int brightness = map(sensorValue, 0, 1023, 0, 255);
  brightness = constrain(brightness, 0, 255);
  
  // Set blue LED to brightness level
  setLED(0, 0, brightness);
  
  // Print to serial monitor
  Serial.print("IR Sensor: ");
  Serial.println(sensorValue);
  Serial.print(" | LED Brightness: ");
  Serial.println(brightness);
  
  // Show visual bar graph
  // Serial.print(" | ");
  // int bars = map(sensorValue, 0, 1023, 0, 40);
  // for (int i = 0; i < bars; i++) {
  //   Serial.print("█");
  // }
  // Serial.println();
  
  delay(100);  // Update 10 times per second
}

// ========== LED CONTROL ==========
// Nano 33 BLE Sense has common anode RGB LED (LOW = ON)
void setLED(int red, int green, int blue) {
  analogWrite(LED_RED, 255 - red);      // Invert for common anode
  analogWrite(LED_GREEN, 255 - green);
  analogWrite(LED_BLUE, 255 - blue);
}

/*
 * TESTING TIPS:
 * 
 * 1. Open Serial Monitor (Tools > Serial Monitor, 115200 baud)
 * 2. Point your IR LED at the BPW34 photodiode
 * 3. You should see:
 *    - Numbers increase in Serial Monitor
 *    - Blue LED brighten on the Arduino
 *    - Bar graph grow longer
 * 
 * 4. Expected readings:
 *    - No IR: 0-50 (baseline noise)
 *    - Weak IR: 50-200
 *    - Strong IR: 200-1023
 * 
 * 5. If readings are stuck at 0:
 *    - Check BPW34 polarity (cathode to 3.3V)
 *    - Verify LM358 pin 8 has 3.3V power
 *    - Confirm feedback resistor between pins 1 and 2
 * 
 * 6. If readings are stuck at 1023:
 *    - Too much IR light or feedback resistor too high
 *    - Try lower value resistor (10kΩ instead of 470kΩ)
 *    - Move IR source farther away
 * 
 * 7. TV Remote test:
 *    - Point TV remote at sensor
 *    - Press and HOLD any button
 *    - Should see rapid pulses in the readings
 */