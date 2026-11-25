
#include <Arduino.h>

// GPIO
constexpr uint8_t LDR_PIN = 4;
constexpr uint8_t RELAY_PIN = 16;

// ADC thresholds (temporary values)
constexpr int THRESHOLD_DARK = 1500;
constexpr int THRESHOLD_LIGHT = 2700;

// Relay state
bool relayEnabled = false;

void setup() {
    Serial.begin(115200);

    analogReadResolution(12);

    // Keep the relay disabled at startup
    digitalWrite(RELAY_PIN, LOW);
    pinMode(RELAY_PIN, OUTPUT);

    Serial.println("Light controller started");
}

void loop() {
    // Read light sensor
    int adcValue = analogRead(LDR_PIN);

    // Hysteresis
    if (adcValue < THRESHOLD_DARK) {
        relayEnabled = true;
    }
    else if (adcValue > THRESHOLD_LIGHT) {
        relayEnabled = false;
    }

    // Control external BC547 transistor
    digitalWrite(RELAY_PIN, relayEnabled ? HIGH : LOW);

    // Debug information
    Serial.print("ADC: ");
    Serial.print(adcValue);

    Serial.print(" | Relay: ");
    Serial.println(relayEnabled ? "ON" : "OFF");

    delay(500);
}
