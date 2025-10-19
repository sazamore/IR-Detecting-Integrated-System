/*
 * Simple IR Sensor Test Code
 * Arduino Nano 33 BLE Sense Rev2
 * 
 * Tests BPW34 + LM358 IR detector circuit
 * LED brightness increases with IR signal strength
 */

// ========== PIN DEFINITIONS ==========
const int IR_SENSOR_PIN = A0;  // IR sensor output from LM358
const int VIBRATION_PIN = 2;   // PWM output for vibration motor

// // RGB LED pins (Nano 33 BLE Sense built-in)
// const int LED_RED = 22;
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
  Serial.println("LED + Vibration will increase with IR intensity\n");
  
  // Initialize pins
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Turn LED and vibration off initially
  setLED(0, 0, 0);
  analogWrite(VIBRATION_PIN, 0);
  
  delay(1000);
  Serial.println("Ready! Watching for IR...\n");
}

// ========== MAIN LOOP ==========
void loop() {
  // Read IR sensor (0-1023 from ADC)
  int sensorValue = analogRead(IR_SENSOR_PIN);
  
  // Map sensor reading to output intensity (0-255)
  int intensity = map(sensorValue, 0, 1023, 0, 255);
  intensity = constrain(intensity, 0, 255);
  
  // Set blue LED to intensity level
  setLED(0, 0, intensity);
  
  // Set vibration motor to same intensity
  analogWrite(VIBRATION_PIN, intensity);
  
  // Print to serial monitor
  Serial.print("IR Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Intensity: ");
  Serial.print(intensity);
  
  // Show visual bar graph
  Serial.print(" | ");
  int bars = map(sensorValue, 0, 1023, 0, 40);
  for (int i = 0; i < bars; i++) {
    Serial.print("█");
  }
  Serial.println();
  
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
 * 3. You should see/feel:
 *    - Numbers increase in Serial Monitor
 *    - Blue LED brighten on the Arduino
 *    - Vibration motor intensity increase
 *    - Bar graph grow longer
 * 
 * 4. Expected readings:
 *    - No IR: 0-50 (baseline noise, no vibration)
 *    - Weak IR: 50-200 (light vibration)
 *    - Strong IR: 200-1023 (strong vibration)
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
 *    - Should see rapid pulses in readings and vibration
 * 
 * 8. Vibration motor troubleshooting:
 *    - If motor doesn't vibrate, test with separate vibromotor test code
 *    - Verify 2N2222 transistor circuit is correct
 *    - Check flyback diode polarity (stripe toward 5V)
 *    - Ensure motor gets 5V power from Arduino
 */