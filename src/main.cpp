#include <Arduino.h>
#include <Servo.h>

const int ldrPin = A0;
const int servoPin = 9;
Servo myServo;

int currentAngle = 90;
int direction = 1;
unsigned long lightStartTime = 0;
bool isStopped = false;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  Serial.println("Night Owl Servo Boot Initialized...");
}

void loop() {
  int lightLevel = analogRead(ldrPin);

  // 1. Check for "Light for too long" (Daytime Sleep)
  // Assuming higher value is darker, lower is brighter
  if (lightLevel < 400) { // If it's light
    if (lightStartTime == 0) {
      lightStartTime = millis(); // Start timing
    }
    
    // If it's been light for more than 3 seconds
    if (millis() - lightStartTime > 3000) {
      isStopped = true;
    }
  } else {
    // Darkness is back! Reset timer and wake up
    lightStartTime = 0;
    isStopped = false;
  }

  // 2. Movement Logic
  if (!isStopped) {
    // Speed: Darker = Faster (Smaller Delay)
    // Dim (400) -> 40ms delay, Dark (800) -> 5ms delay
    int moveDelay = map(lightLevel, 400, 800, 40, 5);
    moveDelay = constrain(moveDelay, 5, 40);

    currentAngle += direction;
    if (currentAngle >= 160 || currentAngle <= 20) {
      direction *= -1;
    }

    myServo.write(currentAngle);
    delay(moveDelay);
  } else {
    // It's light and we are stopped
    Serial.println("STATUS: ASLEEP (Daytime Sleep)");
    delay(500); // Check less frequently while sleeping
  }

    // Debugging

    static unsigned long lastPrint = 0;

    if (millis() - lastPrint > 500 && !isStopped) {

      Serial.print("LDR Value: "); Serial.print(lightLevel);

      Serial.print(" | Speed: "); Serial.print(map(lightLevel, 400, 800, 40, 5)); Serial.println("ms (lower is faster)");

      lastPrint = millis();

    }

  }

  