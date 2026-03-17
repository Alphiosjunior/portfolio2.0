#include <DHT.h>
#include <DHT_U.h>
#include "thingProperties.h"

// Pin definitions for all connected devices
#define STATUS_LED 8           // Main alarm indicator
#define ARM_BUTTON 7           // Security toggle button
#define BEDROOM_SENSOR 3       // Bedroom motion detection
#define LIVINGROOM_SENSOR 4    // Living room motion detection
#define BEDROOM_LIGHT 9        // Bedroom illumination
#define LIVINGROOM_LIGHT 12    // Living room illumination
#define FIRE_SENSOR 2          // Flame detection sensor
#define CLIMATE_PIN 5          // Temperature/humidity sensor
#define DHT_TYPE DHT11         // Climate sensor model
#define FIRE_PUMP 11           // Fire suppression system
#define COOLING_FAN 6          // Temperature regulation fan

// System state tracking
bool fireAlert = false;
bool alarmActive = false;
bool previousButtonState = HIGH;
bool buttonFlag = false;
bool securityActive = false;
bool bedroomMotion = false;
bool livingroomMotion = false;
bool smartClimate = true;
DHT climateSensor(CLIMATE_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  delay(1500); 

  Serial.println("=== Home Control System Initializing ===");
  
  initProperties();
  
  Serial.println("Establishing network connection...");
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Configure all device connections
  pinMode(STATUS_LED, OUTPUT);
  pinMode(BEDROOM_LIGHT, OUTPUT);
  pinMode(LIVINGROOM_LIGHT, OUTPUT);
  pinMode(ARM_BUTTON, INPUT_PULLUP);
  pinMode(BEDROOM_SENSOR, INPUT);
  pinMode(LIVINGROOM_SENSOR, INPUT);
  pinMode(FIRE_SENSOR, INPUT);
  pinMode(FIRE_PUMP, OUTPUT);
  pinMode(COOLING_FAN, OUTPUT);
  digitalWrite(STATUS_LED, alarmActive);
  climateSensor.begin();

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  Serial.println("=== System Ready ===");
}

void loop() {
  ArduinoCloud.update();
  
  // Read environmental conditions
  float currentTemp = climateSensor.readTemperature();
  float currentHumidity = climateSensor.readHumidity();
  
  if (!isnan(currentTemp)) {
    tempareture = currentTemp;
    Serial.print("Current Temperature: ");
    Serial.println(tempareture);
  } else {
    Serial.println("Climate sensor reading failed!");
  }

  // Process security button input
  bool currentButtonState = digitalRead(ARM_BUTTON);
  if (currentButtonState == LOW && previousButtonState == HIGH) {
    buttonFlag = !buttonFlag;
    securityActive = !securityActive;
  }
  previousButtonState = currentButtonState;

  // Update sensor readings
  bedroomMotion = digitalRead(BEDROOM_SENSOR);
  livingroomMotion = digitalRead(LIVINGROOM_SENSOR);
  fireAlert = digitalRead(FIRE_SENSOR);
  fire = fireAlert;

  // Security system logic
  if (fireAlert || (securityActive && (bedroomMotion || livingroomMotion))) {
    alarmActive = true;
  } else {
    alarmActive = false;
  }
  iNTRUDER = alarmActive;
  digitalWrite(STATUS_LED, alarmActive);

  // Lighting management
  if (!securityActive) {
    // Automatic lighting when system disarmed
    if (!bedroom) {
      digitalWrite(BEDROOM_LIGHT, bedroomMotion ? HIGH : LOW);
    }
    if (!livingroom) {
      digitalWrite(LIVINGROOM_LIGHT, livingroomMotion ? HIGH : LOW);
    }
  } else {
    // Lights off during security mode
    digitalWrite(BEDROOM_LIGHT, LOW);
    digitalWrite(LIVINGROOM_LIGHT, LOW);
  }

  // Smart temperature management
  if (smartClimate) {
    if (currentTemp > 30.0) {
      digitalWrite(COOLING_FAN, HIGH);
      Serial.println("Cooling fan activated (Auto)");
    } else {
      digitalWrite(COOLING_FAN, LOW);
      Serial.println("Cooling fan deactivated (Auto)");
    }
  }
  
  delay(50);
}

// Cloud integration functions

void onClimateControlChange() {
  smartClimate = !climateControl;
  if (climateControl) {
    digitalWrite(COOLING_FAN, HIGH);
    Serial.println("Manual climate control - Fan ON");
  } else {
    digitalWrite(COOLING_FAN, LOW);
    Serial.println("Manual climate control - Fan OFF");
  }
}

void onBedroomChange() {
  if(bedroom) {
    digitalWrite(BEDROOM_LIGHT, HIGH);
  } else {
    digitalWrite(BEDROOM_LIGHT, LOW);
  }
}

void onLivingroomChange() {
  if(livingroom) {
    digitalWrite(LIVINGROOM_LIGHT, HIGH);
  } else {
    digitalWrite(LIVINGROOM_LIGHT, LOW);
  }
}

void onSercurityArmChange() {
  securityActive = sercurityArm;
}

void onMapTempChange() {
  // Custom temperature mapping functionality
  // Add your specific implementation here
}