#include <Servo.h>

// Pins 
#define MOISTURE_SENSOR A0
#define SOUND_SENSOR    2 //A1
#define LED             3    // Must be PWM pin
#define BUZZER          4
#define RELAY_PIN       9
#define SERVO_PIN       6

// Constants
#define MOISTURE_THRESHOLD  800

#define FADE_DELAY          5     // ms per brightness step

Servo cradle;

void setup() {
    pinMode(LED,        OUTPUT);
    pinMode(BUZZER,     OUTPUT);
    pinMode(RELAY_PIN,  OUTPUT);

    digitalWrite(LED,       LOW);
    digitalWrite(BUZZER,    LOW);
    digitalWrite(RELAY_PIN, LOW);

    cradle.attach(SERVO_PIN);
    smoothMove(90); // Start at center

    Serial.begin(9600);
    Serial.println("Smart Baby Cradle Ready...");
}

void loop() {
    int moistureValue = analogRead(MOISTURE_SENSOR);
    int soundValue    = digitalRead(SOUND_SENSOR);

    Serial.print("Moisture: ");
    Serial.print(moistureValue);
    Serial.print(" | Sound: ");
    Serial.println(soundValue);

    // Moisture / Wet Diaper 
    // some sensors are high when they are dry
    if (moistureValue < MOISTURE_THRESHOLD) {
        Serial.println("Diaper WET — Buzzer notifying!");
        notifyBuzzer();
    }

    // Crying Detected → Rock + Light + Speaker
    if (soundValue == HIGH) {
        Serial.println("Baby crying — Starting cradle + light + speaker");
        digitalWrite(RELAY_PIN, HIGH);
        notifyBuzzer();
        fadeLED();
        rockCradle();
        
    } else {
        // No Crying = Stop Everything 
        Serial.println("No crying — Stopping everything");
        stopAll();
    }

    delay(30);
}

// Smooth servo movement 
void smoothMove(int targetAngle) {
    static int currentAngle = 90;
    int step = (targetAngle > currentAngle) ? 1 : -1;

    while (currentAngle != targetAngle) {
        currentAngle += step;
        cradle.write(currentAngle);
        delay(12);
    }
}

// Cradle rocking (smooth)
void rockCradle() {
    smoothMove(45);
    delay(30);
    smoothMove(135);
    delay(30);
    smoothMove(90);
}

// LED fade up and down
void fadeLED() {
    for (int b = 1; b <= 120; b++) {
        if (digitalRead(SOUND_SENSOR) == HIGH ) return;
        analogWrite(LED, b);
        delay(FADE_DELAY);
    }
    for (int b = 120; b >= 1; b--) {
        if (digitalRead(SOUND_SENSOR) == HIGH ) return;
        analogWrite(LED, b);
        delay(FADE_DELAY);
    }
}

// Buzzer: short beeps for wet diaper
void notifyBuzzer() {
    for (int i = 0; i < 3 ; i++) {
        digitalWrite(BUZZER, HIGH);
        delay(300);
        digitalWrite(BUZZER, LOW);
        delay(300);
    }
}

//  Stop everything
void stopAll() {
    analogWrite(LED, 0);
    digitalWrite(RELAY_PIN, LOW);
    smoothMove(90);
}
