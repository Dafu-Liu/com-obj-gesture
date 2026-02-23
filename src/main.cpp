#include <Arduino.h>
#include <Servo.h>

const int ldrPin = A0;
const int servoPin = 9;
Servo myServo;

int currentAngle = 90;
int direction = 1;
unsigned long darkStartTime = 0;
bool isStopped = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  Serial.println("LDR Timeout Sweep Initialized...");
}

void loop() {
  int lightLevel = analogRead(ldrPin);

  // 1. Check for "Dark for too long"
  if (lightLevel > 700) {
    if (darkStartTime == 0) {
      darkStartTime = millis(); // Start timing
    }
    
    // If it's been dark for more than 3 seconds
    if (millis() - darkStartTime > 3000) {
      isStopped = true;
    }
  } else {
    // Light is back! Reset timer and wake up
    darkStartTime = 0;
    isStopped = false;
  }

  // 2. Movement Logic
  if (!isStopped) {
    // Speed: Brighter = Faster (Smaller Delay)
    // Bright (200) -> 5ms delay, Dim (600) -> 40ms delay
    int moveDelay = map(lightLevel, 200, 600, 5, 40);
    moveDelay = constrain(moveDelay, 5, 40);

    currentAngle += direction;
    if (currentAngle >= 160 || currentAngle <= 20) {
      direction *= -1;
    }

    myServo.write(currentAngle);
    delay(moveDelay);
  } else {
    // It's dark and we are stopped
    Serial.println("STATUS: ASLEEP (Dark Timeout)");
    delay(500); // Check less frequently while sleeping
  }

  // Debugging
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500 && !isStopped) {
    Serial.print("Light: "); Serial.print(lightLevel);
    Serial.print(" | Moving (Delay: "); Serial.print(map(lightLevel, 200, 600, 5, 40)); Serial.println("ms)");
    lastPrint = millis();
  }
}