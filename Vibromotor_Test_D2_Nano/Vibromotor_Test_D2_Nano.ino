/*
 * Vibration Motor Test Code
 * Arduino Nano 33 BLE Sense Rev2
 * 
 * Simple test for ERM vibration motor with 2N2222 transistor driver
 * Pulses motor at various intensities to verify circuit operation
 */

// ========== PIN DEFINITION ==========
const int VIBRATION_PIN = 2;  // PWM output to 2N2222 base (via 1kΩ resistor)

// ========== TEST PARAMETERS ==========
const int PULSE_DURATION_MS = 500;   // Duration of each pulse
const int PAUSE_DURATION_MS = 500;   // Pause between pulses

// ========== SETUP ==========
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // onboard LED

  Serial.begin(115200);
  
  // Wait for serial connection (optional)
  while (!Serial && millis() < 3000);
  
  Serial.println("=================================");
  Serial.println("Vibration Motor Test");
  Serial.println("=================================");
  Serial.println("Pin D2 → 1kΩ → 2N2222 Base");
  Serial.println("Motor should pulse at varying intensities\n");
  
  // Initialize vibration motor pin as output
  pinMode(VIBRATION_PIN, OUTPUT);
  analogWrite(VIBRATION_PIN, 0);  // Start OFF

  delay(1000);
  Serial.println("Starting test sequence...\n");
}

// ========== MAIN LOOP ==========
void loop() {
  // Test Pattern 1: Intensity Sweep (0% → 100%)
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

  Serial.println("--- Test 1: Intensity Sweep (Low → High) ---");
  for (int intensity = 0; intensity <= 255; intensity += 25) {
    Serial.print("Intensity: ");
    Serial.print(intensity);
    Serial.print(" (");
    Serial.print((int)(intensity / 2.55));
    Serial.println("%)");
    
    analogWrite(VIBRATION_PIN, intensity);
    delay(PULSE_DURATION_MS);
  }
  
  // Turn off
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off 

  analogWrite(VIBRATION_PIN, 0);
  Serial.println("OFF\n");
  delay(PAUSE_DURATION_MS * 2);
  
  
  // Test Pattern 2: Fixed Intensity Pulses
  Serial.println("--- Test 2: Fixed Intensity Pulses ---");
  int testIntensities[] = {64, 128, 192, 255};  // 25%, 50%, 75%, 100%
  
  for (int i = 0; i < 4; i++) {
    Serial.print("Pulse ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(testIntensities[i]);
    Serial.print(" (");
    Serial.print((int)(testIntensities[i] / 2.55));
    Serial.println("%)");
    
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    analogWrite(VIBRATION_PIN, testIntensities[i]);
    delay(PULSE_DURATION_MS);
    
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off (LOW is the voltage level)
    analogWrite(VIBRATION_PIN, 0);
    delay(PAUSE_DURATION_MS);
  }
  Serial.println();
  delay(PAUSE_DURATION_MS);
  
  
  // Test Pattern 3: Rapid Pulses (Buzz Pattern)
  Serial.println("--- Test 3: Rapid Buzz Pattern ---");
  for (int i = 0; i < 5; i++) {
    Serial.print("Buzz ");
    Serial.println(i + 1);
    
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    analogWrite(VIBRATION_PIN, 200);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    analogWrite(VIBRATION_PIN, 0);
    delay(100);
  }
  Serial.println();
  delay(PAUSE_DURATION_MS * 2);
  
  
  // Test Pattern 4: Fade In/Out
  Serial.println("--- Test 4: Smooth Fade In/Out ---");
  
  // Fade in
  Serial.println("Fading in...");
  for (int intensity = 0; intensity <= 255; intensity += 5) {
    analogWrite(VIBRATION_PIN, intensity);
    delay(20);
  }
  
  delay(500);
  
  // Fade out
  Serial.println("Fading out...");
  for (int intensity = 255; intensity >= 0; intensity -= 5) {
    analogWrite(VIBRATION_PIN, intensity);
    delay(20);
  }
  
  analogWrite(VIBRATION_PIN, 0);
  Serial.println("Complete\n");
  delay(PAUSE_DURATION_MS * 2);
  
  
  // Test Pattern 5: SOS Pattern (... --- ...)
  Serial.println("--- Test 5: SOS Morse Code Pattern ---");
  Serial.println("(Short-Short-Short / Long-Long-Long / Short-Short-Short)");
  
  // S (...)
  for (int i = 0; i < 3; i++) {
    analogWrite(VIBRATION_PIN, 255);
    delay(150);
    analogWrite(VIBRATION_PIN, 0);
    delay(150);
  }
  delay(300);
  
  // O (---)
  for (int i = 0; i < 3; i++) {
    analogWrite(VIBRATION_PIN, 255);
    delay(450);
    analogWrite(VIBRATION_PIN, 0);
    delay(150);
  }
  delay(300);
  
  // S (...)
  for (int i = 0; i < 3; i++) {
    analogWrite(VIBRATION_PIN, 255);
    delay(150);
    analogWrite(VIBRATION_PIN, 0);
    delay(150);
  }
  
  Serial.println("SOS Complete\n");
  delay(PAUSE_DURATION_MS * 3);
  
  
  // End of test sequence
  Serial.println("=================================");
  Serial.println("Test sequence complete!");
  Serial.println("Restarting in 3 seconds...");
  Serial.println("=================================\n");
  delay(3000);
}

/*
 * TROUBLESHOOTING:
 * 
 * If motor doesn't vibrate:
 * 1. Check 2N2222 orientation (flat side matches schematic)
 * 2. Verify 1kΩ base resistor is connected
 * 3. Confirm flyback diode (1N4007) is installed (stripe toward 5V)
 * 4. Test motor directly with 3-5V to confirm it works
 * 5. Check transistor with multimeter (should show ~0.7V Vbe when ON)
 * 6. Ensure motor draws < 100mA (if higher, use beefier transistor)
 * 
 * If motor runs constantly:
 * 1. Check for solder bridges on transistor pins
 * 2. Verify base resistor is 1kΩ (not too low)
 * 
 * Expected behavior:
 * - You should feel distinct pulses of varying intensity
 * - Motor should turn OFF completely between pulses
 * - Stronger intensities should be clearly perceptible
 */